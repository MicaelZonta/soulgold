/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "main.h"

#include <mgba/internal/debugger/cli-debugger.h>

#ifdef ENABLE_SCRIPTING
#include <mgba/core/scripting.h>

#ifdef ENABLE_PYTHON
#include "platform/python/engine.h"
#endif
#endif

#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/input.h>
#include <mgba/core/serialize.h>
#include <mgba/core/thread.h>
#include <mgba/internal/gba/input.h>

#include <mgba/feature/commandline.h>
#include <mgba-util/vfs.h>

#include <SDL.h>

#include <errno.h>
#include <signal.h>

#define PORT "sdl"

static void mSDLDeinit(struct mSDLRenderer* renderer);

static int mSDLRun(struct mSDLRenderer* renderer, struct mArguments* args);

static struct mStandardLogger _logger;

#ifdef SOULGOLD_STANDALONE
/* SoulGold standalone: a ROM vem embutida no executavel (objeto gerado com
 * `ld -r -b binary soulgold_rom.bin`, ver tools/standalone/build.sh). No
 * primeiro uso ela e extraida para ao lado do executavel (fallback: pasta de
 * dados do usuario, se a pasta do executavel nao aceitar escrita) e o fluxo
 * segue como `mgba <rom>` - o .sav nasce ao lado da ROM extraida. */
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <sys/stat.h>

extern const unsigned char _binary_soulgold_rom_bin_start[];
extern const unsigned char _binary_soulgold_rom_bin_end[];

static bool _soulgoldSameFile(const char* path, const unsigned char* data, size_t size) {
	FILE* f = fopen(path, "rb");
	if (!f) {
		return false;
	}
	bool same = false;
	if (fseek(f, 0, SEEK_END) == 0 && (size_t) ftell(f) == size) {
		fseek(f, 0, SEEK_SET);
		unsigned char buf[65536];
		size_t off = 0;
		same = true;
		while (off < size) {
			size_t chunk = fread(buf, 1, sizeof(buf), f);
			if (!chunk || memcmp(buf, data + off, chunk) != 0) {
				same = false;
				break;
			}
			off += chunk;
		}
		if (off != size) {
			same = false;
		}
	}
	fclose(f);
	return same;
}

static bool _soulgoldWriteRom(const char* path, const unsigned char* data, size_t size) {
	FILE* f = fopen(path, "wb");
	if (!f) {
		return false;
	}
	bool ok = fwrite(data, 1, size, f) == size;
	fclose(f);
	if (!ok) {
		remove(path);
	}
	return ok;
}

static const char* _soulgoldRomPath(void) {
	/* maior que dir para o sufixo "/Soulgold.gba" caber sem -Wformat-truncation */
	static char path[4352];
	const unsigned char* data = _binary_soulgold_rom_bin_start;
	size_t size = (size_t) (_binary_soulgold_rom_bin_end - _binary_soulgold_rom_bin_start);
	char dir[4096] = {0};
#ifdef _WIN32
	DWORD len = GetModuleFileNameA(NULL, dir, sizeof(dir) - 1);
	while (len > 0 && dir[len - 1] != '\\' && dir[len - 1] != '/') {
		--len;
	}
	dir[len] = '\0';
#else
	ssize_t len = readlink("/proc/self/exe", dir, sizeof(dir) - 1);
	while (len > 0 && dir[len - 1] != '/') {
		--len;
	}
	if (len < 0) {
		len = 0;
	}
	dir[len] = '\0';
#endif
	snprintf(path, sizeof(path), "%sSoulgold.gba", dir);
	if (_soulgoldSameFile(path, data, size) || _soulgoldWriteRom(path, data, size)) {
		return path;
	}
#ifdef _WIN32
	const char* base = getenv("LOCALAPPDATA");
	if (!base) {
		return NULL;
	}
	snprintf(dir, sizeof(dir), "%s\\SoulGold", base);
	_mkdir(dir);
	snprintf(path, sizeof(path), "%s\\Soulgold.gba", dir);
#else
	const char* base = getenv("HOME");
	if (!base) {
		return NULL;
	}
	snprintf(dir, sizeof(dir), "%s/.local/share/SoulGold", base);
	mkdir(dir, 0755);
	snprintf(path, sizeof(path), "%s/Soulgold.gba", dir);
#endif
	if (_soulgoldSameFile(path, data, size) || _soulgoldWriteRom(path, data, size)) {
		return path;
	}
	return NULL;
}
#endif

static struct VFile* _state = NULL;

static void _loadState(struct mCoreThread* thread) {
	mCoreLoadStateNamed(thread->core, _state, SAVESTATE_RTC);
}

int main(int argc, char** argv) {
#ifdef _WIN32
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
#endif
#ifdef SOULGOLD_STANDALONE
	char* soulgoldArgv[2];
	if (argc < 2) {
		const char* soulgoldRom = _soulgoldRomPath();
		if (soulgoldRom) {
			soulgoldArgv[0] = argv[0];
			soulgoldArgv[1] = (char*) soulgoldRom;
			argv = soulgoldArgv;
			argc = 2;
		} else {
			printf("SoulGold: could not extract the embedded ROM to disk\n");
		}
	}
#endif
	struct mSDLRenderer renderer = {0};

	struct mCoreOptions opts = {
		.useBios = true,
		.rewindEnable = true,
		.rewindBufferCapacity = 600,
		.rewindBufferInterval = 1,
		.audioBuffers = 1024,
		.videoSync = false,
		.audioSync = true,
		.volume = 0x100,
		.logLevel = mLOG_WARN | mLOG_ERROR | mLOG_FATAL,
	};

	struct mArguments args;
	struct mGraphicsOpts graphicsOpts;

	struct mSubParser subparser;

	mSubParserGraphicsInit(&subparser, &graphicsOpts);
	bool parsed = mArgumentsParse(&args, argc, argv, &subparser, 1);
	if (!args.fname && !args.showVersion) {
		parsed = false;
	}
	if (!parsed || args.showHelp) {
		usage(argv[0], NULL, NULL, &subparser, 1);
		mArgumentsDeinit(&args);
		return !parsed;
	}
	if (args.showVersion) {
		version(argv[0]);
		mArgumentsDeinit(&args);
		return 0;
	}

	if (!SDL_OK(SDL_Init(SDL_INIT_VIDEO))) {
		printf("Could not initialize video: %s\n", SDL_GetError());
		mArgumentsDeinit(&args);
		return 1;
	}

	renderer.core = mCoreFind(args.fname);
	if (!renderer.core) {
		printf("Could not run game. Are you sure the file exists and is a compatible game?\n");
		mArgumentsDeinit(&args);
		return 1;
	}

	if (!renderer.core->init(renderer.core)) {
		mArgumentsDeinit(&args);
		return 1;
	}

	renderer.core->baseVideoSize(renderer.core, &renderer.width, &renderer.height);
	renderer.ratio = graphicsOpts.multiplier;
#ifdef SOULGOLD_STANDALONE
	/* Sem argumento de escala, 240x160 e minusculo num monitor moderno. */
	if (renderer.ratio == 0) {
		renderer.ratio = 4;
	}
#endif
	if (renderer.ratio == 0) {
		renderer.ratio = 1;
	}
	opts.width = renderer.width * renderer.ratio;
	opts.height = renderer.height * renderer.ratio;

	mInputMapInit(&renderer.core->inputMap, &GBAInputInfo);
	mCoreInitConfig(renderer.core, PORT);
	mArgumentsApply(&args, &subparser, 1, &renderer.core->config);

	mCoreConfigSetDefaultIntValue(&renderer.core->config, "logToStdout", true);
	mCoreConfigLoadDefaults(&renderer.core->config, &opts);
	mCoreLoadConfig(renderer.core);
	mStandardLoggerInit(&_logger);
	mStandardLoggerConfig(&_logger, &renderer.core->config);
	mLogSetDefaultLogger(&_logger.d);

	renderer.viewportWidth = renderer.core->opts.width;
	renderer.viewportHeight = renderer.core->opts.height;
	renderer.player.fullscreen = renderer.core->opts.fullscreen;
	renderer.player.windowUpdated = 0;

	renderer.lockAspectRatio = renderer.core->opts.lockAspectRatio;
	renderer.lockIntegerScaling = renderer.core->opts.lockIntegerScaling;
	renderer.interframeBlending = renderer.core->opts.interframeBlending;
	renderer.filter = renderer.core->opts.resampleVideo;

#ifdef BUILD_GL
	if (mSDLGLCommonInit(&renderer)) {
		mSDLGLCreate(&renderer);
	} else
#elif defined(BUILD_GLES2) || defined(USE_EPOXY)
	if (mSDLGLCommonInit(&renderer))
	{
		mSDLGLES2Create(&renderer);
	} else
#endif
	{
		mSDLSWCreate(&renderer);
	}

	if (!renderer.init(&renderer)) {
		mArgumentsDeinit(&args);
		mCoreConfigDeinit(&renderer.core->config);
		renderer.core->deinit(renderer.core);
		return 1;
	}

	renderer.player.bindings = &renderer.core->inputMap;
	mSDLInitBindingsGBA(&renderer.core->inputMap);
	mSDLInitEvents(&renderer.events);
	mSDLEventsLoadConfig(&renderer.events, mCoreConfigGetInput(&renderer.core->config));
	mSDLAttachPlayer(&renderer.events, &renderer.player, -1);
	mSDLPlayerLoadConfig(&renderer.player, mCoreConfigGetInput(&renderer.core->config));

#if SDL_VERSION_ATLEAST(2, 0, 0)
	renderer.core->setPeripheral(renderer.core, mPERIPH_RUMBLE, &renderer.player.rumble.d.d);
#endif

	int ret;

	// TODO: Use opts and config
	ret = mSDLRun(&renderer, &args);
	mSDLDetachPlayer(&renderer.events, &renderer.player);
	mInputMapDeinit(&renderer.core->inputMap);

	mSDLDeinit(&renderer);
	mStandardLoggerDeinit(&_logger);

	mArgumentsDeinit(&args);
	mCoreConfigFreeOpts(&opts);
	mCoreConfigDeinit(&renderer.core->config);
	renderer.core->deinit(renderer.core);

	return ret;
}

#if defined(_WIN32) && !defined(_UNICODE)
#include <mgba-util/string.h>

int wmain(int argc, wchar_t** argv) {
	char** argv8 = malloc(sizeof(char*) * argc);
	int i;
	for (i = 0; i < argc; ++i) {
		argv8[i] = utf16to8((uint16_t*) argv[i], wcslen(argv[i]) * 2);
	}
	__argv = argv8;
	int ret = main(argc, argv8);
	for (i = 0; i < argc; ++i) {
		free(argv8[i]);
	}
	free(argv8);
	return ret;
}
#endif

int mSDLRun(struct mSDLRenderer* renderer, struct mArguments* args) {
	struct mCoreThread thread = {
		.core = renderer->core
	};
	if (!mCoreLoadFile(renderer->core, args->fname)) {
		return 1;
	}
	mCoreAutoloadSave(renderer->core);
	mArgumentsApplyFileLoads(args, renderer->core);
#ifdef ENABLE_SCRIPTING
	struct mScriptBridge* bridge = mScriptBridgeCreate();
#ifdef ENABLE_PYTHON
	mPythonSetup(bridge);
#endif
#ifdef ENABLE_DEBUGGERS
	CLIDebuggerScriptEngineInstall(bridge);
#endif
#endif

#ifdef ENABLE_DEBUGGERS
	struct mDebugger debugger;
	mDebuggerInit(&debugger);
	bool hasDebugger = mArgumentsApplyDebugger(args, renderer->core, &debugger);

	if (hasDebugger) {
		mDebuggerAttach(&debugger, renderer->core);
		mDebuggerEnter(&debugger, DEBUGGER_ENTER_MANUAL, NULL);
#ifdef ENABLE_SCRIPTING
		mScriptBridgeSetDebugger(bridge, &debugger);
#endif
	} else {
		mDebuggerDeinit(&debugger);
	}
#endif

	renderer->audio.samples = renderer->core->opts.audioBuffers;
	renderer->audio.sampleRate = 44100;
	thread.logger.logger = &_logger.d;

	bool didFail = !mCoreThreadStart(&thread);

	if (!didFail) {
#if SDL_VERSION_ATLEAST(2, 0, 0)
		renderer->core->currentVideoSize(renderer->core, &renderer->width, &renderer->height);
		unsigned width = renderer->width * renderer->ratio;
		unsigned height = renderer->height * renderer->ratio;
		if (width != (unsigned) renderer->viewportWidth && height != (unsigned) renderer->viewportHeight) {
			SDL_SetWindowSize(renderer->window, width, height);
			renderer->player.windowUpdated = 1;
		}
		mSDLSetScreensaverSuspendable(&renderer->events, renderer->core->opts.suspendScreensaver);
		mSDLSuspendScreensaver(&renderer->events);
#endif
		if (mSDLInitAudio(&renderer->audio, &thread)) {
			if (args->savestate) {
				struct VFile* state = VFileOpen(args->savestate, O_RDONLY);
				if (state) {
					_state = state;
					mCoreThreadRunFunction(&thread, _loadState);
					_state = NULL;
					state->close(state);
				}
			}
			renderer->runloop(renderer, &thread);
			mSDLPauseAudio(&renderer->audio);
			if (mCoreThreadHasCrashed(&thread)) {
				didFail = true;
				printf("The game crashed!\n");
				mCoreThreadEnd(&thread);
			}
		} else {
			didFail = true;
			printf("Could not initialize audio.\n");
		}
#if SDL_VERSION_ATLEAST(2, 0, 0)
		mSDLResumeScreensaver(&renderer->events);
		mSDLSetScreensaverSuspendable(&renderer->events, false);
#endif

		mCoreThreadJoin(&thread);
	} else {
		printf("Could not run game. Are you sure the file exists and is a compatible game?\n");
	}
	renderer->core->unloadROM(renderer->core);

#ifdef ENABLE_SCRIPTING
	mScriptBridgeDestroy(bridge);
#endif

#ifdef ENABLE_DEBUGGERS
	if (hasDebugger) {
		renderer->core->detachDebugger(renderer->core);
		mDebuggerDeinit(&debugger);
	}
#endif

	return didFail;
}

static void mSDLDeinit(struct mSDLRenderer* renderer) {
	mSDLDeinitEvents(&renderer->events);
	mSDLDeinitAudio(&renderer->audio);
#if SDL_VERSION_ATLEAST(2, 0, 0)
	SDL_DestroyWindow(renderer->window);
#endif

	renderer->deinit(renderer);

	SDL_Quit();
}
