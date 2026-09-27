// POC: headless runner for the 96 MiB linear-ROM experiment.
//
// Loads a ROM in libmgba, follows a tiny input script and reports:
//   - screenshots (PNG) at chosen points,
//   - audio RMS per window (proves sound data is being read),
//   - how many "Out of bounds ROM" / "invalid address" errors mGBA logged.
//
// Script lines (one per line, '#' comments):
//   F <n>             run n frames with no keys
//   K <keys> <n>      hold keys (A,B,L,R,START,SELECT,UP,DOWN,LEFT,RIGHT joined by '+') for n frames
//   T <keys> <n>      tap keys: 1 frame down, 1 frame up, repeated n times... (n taps, 20 frames apart)
//   S <name>          screenshot to <outdir>/<name>.png
//   A <label>         print audio RMS accumulated since the previous A
//   SS                save an emulator savestate in memory
//   LS                load the savestate saved by SS
//   V <file>          write the in-game save (Flash) to <outdir>/<file>
//
// With ROMRUN_PATCH=1 in the environment, a <rom>.bps/.ups/.ips next to the ROM
// is applied before reset (tests the emulator's soft-patch path).
//
// Usage: romrun <rom> <outdir> <script>

#include <mgba/core/core.h>
#include <mgba/internal/gba/gba.h>
#include <mgba/core/log.h>
#include <mgba-util/audio-buffer.h>
#include <mgba-util/image/png-io.h>
#include <mgba-util/vfs.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int sOobErrors = 0;
static int sPrinted = 0;
static double sAudioSq = 0;
static long sAudioN = 0;
static struct mCore* core;
static mColor* sVideo;
static int16_t sSamples[0x4000];

static void _log(struct mLogger* logger, int category, enum mLogLevel level, const char* format, va_list args) {
	(void) logger;
	char buf[512];
	vsnprintf(buf, sizeof(buf), format, args);
	if (strstr(buf, "Out of bounds ROM") || strstr(buf, "invalid address") || strstr(buf, "Bad cartridge")) {
		if (++sOobErrors <= 5) {
			fprintf(stderr, "[oob] %s\n", buf);
		}
	}
	if ((level & (mLOG_FATAL | mLOG_ERROR | mLOG_GAME_ERROR | mLOG_WARN)) && sPrinted < 10) {
		++sPrinted;
		fprintf(stderr, "[mgba %s] %s\n", mLogCategoryName(category), buf);
	}
}

static uint32_t _keys(const char* s) {
	static const char* names[] = { "A", "B", "SELECT", "START", "RIGHT", "LEFT", "UP", "DOWN", "R", "L" };
	uint32_t keys = 0;
	char tmp[128];
	strncpy(tmp, s, sizeof(tmp) - 1);
	tmp[sizeof(tmp) - 1] = 0;
	for (char* tok = strtok(tmp, "+"); tok; tok = strtok(NULL, "+")) {
		for (unsigned i = 0; i < sizeof(names) / sizeof(*names); ++i) {
			if (!strcmp(tok, names[i])) {
				keys |= 1 << i;
			}
		}
	}
	return keys;
}

static void _frame(uint32_t keys) {
	core->setKeys(core, keys);
	core->runFrame(core);
	struct mAudioBuffer* ab = core->getAudioBuffer(core);
	size_t avail;
	while ((avail = mAudioBufferAvailable(ab)) > 0) {
		if (avail > sizeof(sSamples) / sizeof(*sSamples) / 2) {
			avail = sizeof(sSamples) / sizeof(*sSamples) / 2;
		}
		size_t got = mAudioBufferRead(ab, sSamples, avail);
		for (size_t i = 0; i < got * 2; ++i) {
			sAudioSq += (double) sSamples[i] * sSamples[i];
		}
		sAudioN += got * 2;
		if (!got) {
			break;
		}
	}
}

static void _shot(const char* dir, const char* name) {
	unsigned w, h;
	core->currentVideoSize(core, &w, &h);
	char path[1024];
	snprintf(path, sizeof(path), "%s/%s.png", dir, name);
	struct VFile* vf = VFileOpen(path, O_CREAT | O_TRUNC | O_WRONLY);
	png_structp png = PNGWriteOpen(vf);
	png_infop info = PNGWriteHeader(png, w, h, mCOLOR_NATIVE);
	PNGWritePixels(png, w, h, 256, sVideo, mCOLOR_NATIVE);
	PNGWriteClose(png, info);
	vf->close(vf);
}

int main(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr, "usage: %s <rom> <outdir> <script>\n", argv[0]);
		return 2;
	}
	struct mLogger logger = { .log = _log };
	mLogSetDefaultLogger(&logger);

	core = mCoreFind(argv[1]);
	if (!core || !core->init(core)) {
		fprintf(stderr, "no core\n");
		return 1;
	}
	mCoreInitConfig(core, NULL);
	sVideo = calloc(256 * 256, sizeof(mColor));
	core->setVideoBuffer(core, sVideo, 256);
	core->setAudioBufferSize(core, 2048);
	if (!mCoreLoadFile(core, argv[1])) {
		fprintf(stderr, "load failed\n");
		return 1;
	}
	if (getenv("ROMRUN_PATCH")) {
		// Soft-patch <rom>.bps/.ups/.ips next to the ROM, like the GUI does.
		bool loaded = mCoreAutoloadPatch(core);
		struct GBA* gba = core->board;
		printf("autoload patch: %s (memory.romSize %zu bytes, romAddrMask 0x%08X)\n", loaded ? "ok" : "none/FAILED", gba->memory.romSize, gba->memory.romAddrMask);
	}
	core->reset(core);

	void* state = NULL;
	FILE* script = fopen(argv[3], "r");
	char line[256];
	long frames = 0;
	while (script && fgets(line, sizeof(line), script)) {
		char op[8], a[128];
		int n = 0;
		if (line[0] == '#' || sscanf(line, "%7s", op) != 1) {
			continue;
		}
		if (!strcmp(op, "F") && sscanf(line, "%*s %d", &n) == 1) {
			for (int i = 0; i < n; ++i, ++frames) _frame(0);
		} else if (!strcmp(op, "K") && sscanf(line, "%*s %127s %d", a, &n) == 2) {
			uint32_t k = _keys(a);
			for (int i = 0; i < n; ++i, ++frames) _frame(k);
		} else if (!strcmp(op, "T") && sscanf(line, "%*s %127s %d", a, &n) == 2) {
			uint32_t k = _keys(a);
			for (int t = 0; t < n; ++t) {
				for (int i = 0; i < 4; ++i, ++frames) _frame(k);
				for (int i = 0; i < 16; ++i, ++frames) _frame(0);
			}
		} else if (!strcmp(op, "S") && sscanf(line, "%*s %127s", a) == 1) {
			_shot(argv[2], a);
			printf("shot %-24s frame %ld\n", a, frames);
		} else if (!strcmp(op, "SS")) {
			free(state);
			state = malloc(core->stateSize(core));
			printf("savestate save: %s (%zu bytes)\n", core->saveState(core, state) ? "ok" : "FAILED", core->stateSize(core));
		} else if (!strcmp(op, "LS")) {
			printf("savestate load: %s\n", state && core->loadState(core, state) ? "ok" : "FAILED");
		} else if (!strcmp(op, "V") && sscanf(line, "%*s %127s", a) == 1) {
			void* sram = NULL;
			size_t size = core->savedataClone(core, &sram);
			char path[1024];
			snprintf(path, sizeof(path), "%s/%s", argv[2], a);
			FILE* f = fopen(path, "wb");
			fwrite(sram, 1, size, f);
			fclose(f);
			size_t used = 0;
			for (size_t i = 0; i < size; ++i) used += ((uint8_t*) sram)[i] != 0xFF;
			printf("savedata %s: %zu bytes, %zu non-0xFF\n", a, size, used);
			free(sram);
		} else if (!strcmp(op, "A") && sscanf(line, "%*s %127s", a) == 1) {
			double rms = sAudioN ? sqrt(sAudioSq / sAudioN) : 0;
			printf("audio %-23s rms %8.1f  (%ld samples)\n", a, rms, sAudioN);
			sAudioSq = 0;
			sAudioN = 0;
		}
	}
	printf("frames %ld, out-of-bounds/invalid ROM accesses logged: %d\n", frames, sOobErrors);
	core->deinit(core);
	return 0;
}
