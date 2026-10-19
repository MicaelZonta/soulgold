#include "global.h"
#include "bg.h"
#include "buenas_password.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "pokegear_radio.h"
#include "pokemon.h"
#include "random.h"
#include "region_map.h"
#include "regions.h"
#include "rtc.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/characters.h"
#include "constants/pokedex.h"
#include "constants/flags.h"
#include "constants/region_map_sections.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/vars.h"

#define TAG_RADIO_DIAL 0x6790
#define PAL_TAG_RADIO_DIAL 0x6790

#define RADIO_TUNING_MIN 0
#define RADIO_TUNING_MAX 63
#define RADIO_DEFAULT_TUNING_POS 13
#define RADIO_DIAL_BASE_X 144
#define RADIO_DIAL_Y 28
#define RADIO_TUNE_DELAY 3
#define RADIO_LINE_HEIGHT 16
#define RADIO_SCROLL_DELAY 90
#define RADIO_MAX_LINES 16
#define RADIO_LINE_BUFFER_SIZE 40
#define RADIO_LINE_PIXEL_WIDTH (28 * 8 - 4)

#define RADIO_FRAME_BASE_TILE 150
#define RADIO_FRAME_PALETTE 4
#define RADIO_TEXT_PALETTE 5

enum RadioStation
{
    RADIO_STATION_NONE,
    RADIO_STATION_POKEMON_TALK,
    RADIO_STATION_POKEMON_MUSIC,
    RADIO_STATION_BUENAS_PASSWORD,
    RADIO_STATION_UNOWN,
    RADIO_STATION_ROCKET,
    // Stations ported from Pokemon HnS (pokenav_radio.c)
    RADIO_STATION_POKEDEX_SHOW,     // shares the Pokemon Talk frequency, mornings only
    RADIO_STATION_LUCKY_CHANNEL,
    RADIO_STATION_PLACES_AND_PEOPLE,
    RADIO_STATION_LETS_ALL_SING,
    RADIO_STATION_POKE_FLUTE,
    RADIO_STATION_EVOLUTION,
    RADIO_STATION_HOENN_SOUND,
};

struct RadioChannel
{
    u8 tuningPos;
    u8 station;
    const u8 *name;
};

struct PokegearRadioResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 tuningPos;
    u8 tuneDelay;
    u8 currentStation;
    u8 dialSpriteId;
    u8 stationNameWindowId;
    u8 radioTextWindowId;
    u8 currentLine;
    u8 numLines;
    bool8 needsScroll;
    u16 scrollTimer;
    u16 currentMusic;
    const u8 *lines[RADIO_MAX_LINES];
    u8 lineBuffer[RADIO_LINE_BUFFER_SIZE];
    u8 topicLineBuffers[RADIO_MAX_LINES][RADIO_LINE_BUFFER_SIZE];
    u16 bg1TilemapBuffer[BG_SCREEN_SIZE / 2];
    u16 bg2TilemapBuffer[BG_SCREEN_SIZE / 2];
};

static EWRAM_DATA struct PokegearRadioResources *sRadio = NULL;
static EWRAM_DATA u8 sLastTuningPos = 0;
static EWRAM_DATA bool8 sHasLastTuningPos = FALSE;

static void CB2_PokegearRadioSetup(void);
static bool8 PokegearRadioDoGfxSetup(void);
static void CB2_PokegearRadioMain(void);
static void VBlankCB_PokegearRadio(void);
static void Task_PokegearRadioInput(u8 taskId);
static void Task_ExitPokegearRadio(u8 taskId);
static void FreePokegearRadioResources(void);
static u8 FindStation(u8 tuningPos);
static bool8 IsStationAvailable(u8 station);
static void UpdateTuning(void);
static void GenerateStationContent(u8 station);
static void AddRadioLine(const u8 *text);
static void AddRadioTopic(const u8 *text);
static void PrintStationName(u8 station);
static void PrintFirstRadioLine(void);
static void ScrollRadioText(void);

static const u16 sRadioUIPal[] = INCBIN_U16("graphics/pokegear/radio/ui.gbapal");
static const u32 sRadioUIGfx[] = INCBIN_U32("graphics/pokegear/radio/ui_tiles.4bpp.smol");
static const u32 sRadioUITilemap[] = INCBIN_U32("graphics/pokegear/radio/ui_map.bin.smolTM");
static const u32 sRadioDialGfx[] = INCBIN_U32("graphics/pokegear/radio/dial.4bpp.smol");

static const u8 sText_NoStation[] = _("- - - -");
static const u8 sText_OaksPokemonTalk[] = _("Oak's Pokémon Talk");
static const u8 sText_PokemonMusic[] = _("Pokémon Music");
static const u8 sText_BuenasPassword[] = _("Buena's Password");
static const u8 sText_UnownStation[] = _("?????");
static const u8 sText_TeamRocket[] = _("Team Rocket");
static const u8 sText_PokedexShow[] = _("Pokédex Show");
static const u8 sText_LuckyChannel[] = _("Lucky Channel");
static const u8 sText_PlacesAndPeople[] = _("Places & People");
static const u8 sText_LetsAllSing[] = _("Let's All Sing!");
static const u8 sText_PokeFlute[] = _("Poké Flute");
static const u8 sText_HoennSound[] = _("Hoenn Sound");

static const u8 sText_Music1[] = _("Ben: Pokémon Music Channel!");
static const u8 sText_Music2[] = _("It's me, DJ Ben!");
static const u8 sText_Music3March[] = _("Today's tune is Pokémon March!");
static const u8 sText_Music3Lullaby[] = _("Today's tune is Pokémon Lullaby!");
static const u8 sText_Fern1[] = _("Fern: Pokémusic!");
static const u8 sText_Fern2[] = _("With DJ Fern!");

static const u8 sText_Hoenn1[] = _("A Pokémon melody from a");
static const u8 sText_Hoenn2[] = _("faraway region called Hoenn!");
static const u8 sText_Hoenn3[] = _("Wild Pokémon from that region");
static const u8 sText_Hoenn4[] = _("may appear nearby!");

static const u8 sText_PokedexShow1[] = _("Oak's Pokédex Show!");
static const u8 sText_PokedexShow2[] = _("Oak: Today's Pokémon is ");
static const u8 sText_PokedexShowEmpty[] = _("No Pokémon on the show today.");

static const u8 sText_Lucky1[] = _("Reed: Yeehaw! How y'all doin'");
static const u8 sText_Lucky2[] = _("now? Whether you're up or way");
static const u8 sText_Lucky3[] = _("down low, don't you miss the");
static const u8 sText_Lucky4[] = _("Lucky Number Show!");
static const u8 sText_Lucky5[] = _("This week's Lucky Number is");
static const u8 sText_LuckyRepeat[] = _("I'll repeat that!");
static const u8 sText_LuckyMatch[] = _("Match it and go to");
static const u8 sText_LuckyTower[] = _("the Radio Tower!");
static const u8 sText_LuckyDrag1[] = _("…Repeating myself");
static const u8 sText_LuckyDrag2[] = _("gets to be a drag…");

static const u8 sText_PnP1[] = _("Places and People! Brought");
static const u8 sText_PnP2[] = _("to you by me, DJ Lily!");
static const u8 sText_Space[] = _(" ");

static const u8 sText_PnP_Cute[] = _("is cute.");
static const u8 sText_PnP_Lazy[] = _("is sort of lazy.");
static const u8 sText_PnP_Happy[] = _("is always happy.");
static const u8 sText_PnP_Noisy[] = _("is quite noisy.");
static const u8 sText_PnP_Precocious[] = _("is precocious.");
static const u8 sText_PnP_Bold[] = _("is somewhat bold.");
static const u8 sText_PnP_Picky[] = _("is too picky!");
static const u8 sText_PnP_SortOfOK[] = _("is sort of OK.");
static const u8 sText_PnP_SoSo[] = _("is just so-so.");
static const u8 sText_PnP_Great[] = _("is actually great.");
static const u8 sText_PnP_MyType[] = _("is just my type.");
static const u8 sText_PnP_Cool[] = _("is so cool, no?");
static const u8 sText_PnP_Inspiring[] = _("is inspiring!");
static const u8 sText_PnP_Weird[] = _("is kind of weird.");
static const u8 sText_PnP_RightForMe[] = _("is right for me?");
static const u8 sText_PnP_Odd[] = _("is definitely odd!");

static const u8 *const sPnPAdjectives[] =
{
    sText_PnP_Cute,
    sText_PnP_Lazy,
    sText_PnP_Happy,
    sText_PnP_Noisy,
    sText_PnP_Precocious,
    sText_PnP_Bold,
    sText_PnP_Picky,
    sText_PnP_SortOfOK,
    sText_PnP_SoSo,
    sText_PnP_Great,
    sText_PnP_MyType,
    sText_PnP_Cool,
    sText_PnP_Inspiring,
    sText_PnP_Weird,
    sText_PnP_RightForMe,
    sText_PnP_Odd,
};

// Places mentioned by Places & People (Kanto, as in HnS).
static const u16 sPnPPlaces[] =
{
    MAPSEC_PALLET_TOWN,
    MAPSEC_ROUTE_22,
    MAPSEC_PEWTER_CITY,
    MAPSEC_CERULEAN_CITY,
    MAPSEC_ROUTE_12,
    MAPSEC_ROUTE_11,
    MAPSEC_ROUTE_16,
    MAPSEC_ROUTE_14,
    MAPSEC_CINNABAR_ISLAND,
};

// Hoenn themes the Hoenn Sound station picks from (HnS list).
static const u16 sHoennSoundSongs[] =
{
    MUS_ROUTE101,
    MUS_ROUTE104,
    MUS_ROUTE110,
    MUS_ROUTE113,
    MUS_ROUTE119,
    MUS_ROUTE120,
    MUS_ROUTE122,
};

static const u8 sText_Buena1[] = _("Buena: Buena here!");
static const u8 sText_Buena2[] = _("Time for today's password!");
static const u8 sText_Buena3[] = _("Today's password is…");
static const u8 sText_BuenaPassword[] = _("{STR_VAR_1}!");
static const u8 sText_Buena4[] = _("Don't forget it! I'm in");
static const u8 sText_Buena5[] = _("Goldenrod's Radio Tower!");
static const u8 sText_BuenaOffAir1[] = _("Buena's Password is off air.");
static const u8 sText_BuenaOffAir2[] = _("Tune in from 6 PM to midnight!");

static const u8 sText_Unown1[] = _("????????????????????????????");
static const u8 sText_Unown2[] = _("????????????????????????????");

static const u8 sText_Rocket1[] = _("… …Ahem, we are");
static const u8 sText_Rocket2[] = _("Team Rocket!");
static const u8 sText_Rocket3[] = _("After three years of preparation,");
static const u8 sText_Rocket4[] = _("we have risen from the ashes!");
static const u8 sText_Rocket5[] = _("Giovanni! Can you hear us?");

static const u8 *const sOakTalkTopics[] =
{
    gText_OakTalk_Lapras,
    gText_OakTalk_Ampharos,
    gText_OakTalk_Sudowoodo,
    gText_OakTalk_RedGyarados,
    gText_OakTalk_Unown,
    gText_OakTalk_Slowpoke,
    gText_OakTalk_LavenderTower,
    gText_OakTalk_TentacruelWhirl,
};

// Crystal frequencies (0-80) scaled to the 64 positions used by this dial.
static const struct RadioChannel sRadioChannels[] =
{
    { 13, RADIO_STATION_POKEMON_TALK,    sText_OaksPokemonTalk },
    { 22, RADIO_STATION_POKEMON_MUSIC,   sText_PokemonMusic },
    { 32, RADIO_STATION_BUENAS_PASSWORD, sText_BuenasPassword },
    { 41, RADIO_STATION_UNOWN,           sText_UnownStation },
    // HnS stations. Tuning positions are the HnS ones (same Crystal scale).
    {  5, RADIO_STATION_HOENN_SOUND,         sText_HoennSound },
    { 25, RADIO_STATION_LUCKY_CHANNEL,       sText_LuckyChannel },
    { 50, RADIO_STATION_PLACES_AND_PEOPLE,   sText_PlacesAndPeople },
    { 57, RADIO_STATION_LETS_ALL_SING,       sText_LetsAllSing },
    { 61, RADIO_STATION_POKE_FLUTE,          sText_PokeFlute },
    { 63, RADIO_STATION_EVOLUTION,           sText_UnownStation },
};

static const struct BgTemplate sRadioBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sRadioWindowTemplates[] =
{
    {
        .bg = 1,
        .tilemapLeft = 6,
        .tilemapTop = 8,
        .width = 19,
        .height = 4,
        .paletteNum = 2,
        .baseBlock = 200,
    },
    {
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 13,
        .width = 28,
        .height = 4,
        .paletteNum = RADIO_TEXT_PALETTE,
        .baseBlock = 1,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u8 sStationNameTextColors[] = {TEXT_COLOR_TRANSPARENT, 7, 5};
static const u8 sRadioTextColors[] = {TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};

static const struct CompressedSpriteSheet sRadioDialSpriteSheet =
{
    .data = sRadioDialGfx,
    .size = 16 * 16 / 2,
    .tag = TAG_RADIO_DIAL,
};

static const struct SpritePalette sRadioDialSpritePalette =
{
    .data = sRadioUIPal,
    .tag = PAL_TAG_RADIO_DIAL,
};

static const struct OamData sRadioDialOam =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1,
};

static const struct SpriteTemplate sRadioDialSpriteTemplate =
{
    .tileTag = TAG_RADIO_DIAL,
    .paletteTag = PAL_TAG_RADIO_DIAL,
    .oam = &sRadioDialOam,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

void OpenPokegearRadio(MainCallback callback)
{
    if (callback == NULL)
        callback = CB2_ReturnToField;

    sRadio = AllocZeroed(sizeof(*sRadio));
    if (sRadio == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sRadio->savedCallback = callback;
    if (!sHasLastTuningPos)
    {
        sLastTuningPos = RADIO_DEFAULT_TUNING_POS;
        sHasLastTuningPos = TRUE;
    }
    sRadio->tuningPos = sLastTuningPos;
    sRadio->dialSpriteId = MAX_SPRITES;
    sRadio->currentMusic = GetCurrentMapMusic();
    gMain.state = 0;
    SetMainCallback2(CB2_PokegearRadioSetup);
}

static void CB2_PokegearRadioSetup(void)
{
    while (TRUE)
    {
        if (PokegearRadioDoGfxSetup())
            break;
    }
}

static bool8 PokegearRadioDoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ResetVramOamAndBgCntRegs();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        ResetAllBgsCoordinates();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sRadioBgTemplates, ARRAY_COUNT(sRadioBgTemplates));
        SetBgTilemapBuffer(1, sRadio->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sRadio->bg2TilemapBuffer);
        FillBgTilemapBufferRect(1, 0, 0, 0, 32, 32, 0);
        ChangeBgX(2, 0x800, BG_COORD_SET);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        gMain.state++;
        break;
    case 3:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sRadioUIGfx, 0, 0, 0);
        CopyToBgTilemapBuffer(2, sRadioUITilemap, 0, 0);
        LoadPalette(sRadioUIPal, BG_PLTT_ID(2), sizeof(sRadioUIPal));
        gMain.state++;
        break;
    case 4:
        if (FreeTempTileDataBuffersIfPossible())
            break;
        LoadCompressedSpriteSheet(&sRadioDialSpriteSheet);
        LoadSpritePalette(&sRadioDialSpritePalette);
        InitWindows(sRadioWindowTemplates);
        DeactivateAllTextPrinters();
        sRadio->stationNameWindowId = 0;
        sRadio->radioTextWindowId = 1;
        LoadPalette(gStandardMenuPalette, BG_PLTT_ID(RADIO_TEXT_PALETTE), PLTT_SIZE_4BPP);
        LoadUserWindowBorderGfx(sRadio->radioTextWindowId, RADIO_FRAME_BASE_TILE, BG_PLTT_ID(RADIO_FRAME_PALETTE));
        DrawStdFrameWithCustomTileAndPalette(sRadio->radioTextWindowId, FALSE, RADIO_FRAME_BASE_TILE, RADIO_FRAME_PALETTE);
        PutWindowTilemap(sRadio->stationNameWindowId);
        PutWindowTilemap(sRadio->radioTextWindowId);
        sRadio->dialSpriteId = CreateSprite(&sRadioDialSpriteTemplate,
                                             RADIO_DIAL_BASE_X + sRadio->tuningPos,
                                             RADIO_DIAL_Y,
                                             1);
        UpdateTuning();
        ScheduleBgCopyTilemapToVram(1);
        ScheduleBgCopyTilemapToVram(2);
        ShowBg(1);
        ShowBg(2);
        CreateTask(Task_PokegearRadioInput, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_PokegearRadio);
        SetMainCallback2(CB2_PokegearRadioMain);
        return TRUE;
    }

    return FALSE;
}

static void CB2_PokegearRadioMain(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_PokegearRadio(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 IsRocketTakeoverActive(void)
{
    u16 state = VarGet(VAR_GOLDENROD_CITY_STATE);

    return state >= 6 && state < 10;
}

static bool8 IsStationAvailable(u8 station)
{
    switch (station)
    {
    case RADIO_STATION_UNOWN:
        return gMapHeader.regionMapSectionId == MAPSEC_RUINS_OF_ALPH;
    case RADIO_STATION_LUCKY_CHANNEL:
        return IsPlayerInJohto();
    case RADIO_STATION_EVOLUTION:
        return !FlagGet(FLAG_HIDE_MAHOGANY_ROCKETS)
            && (gMapHeader.regionMapSectionId == MAPSEC_MAHOGANY_TOWN
             || gMapHeader.regionMapSectionId == MAPSEC_ROUTE_43
             || gMapHeader.regionMapSectionId == MAPSEC_LAKE_OF_RAGE);
    case RADIO_STATION_PLACES_AND_PEOPLE:
    case RADIO_STATION_LETS_ALL_SING:
    case RADIO_STATION_POKE_FLUTE:
    case RADIO_STATION_HOENN_SOUND:
        return !IsPlayerInJohto() && FlagGet(FLAG_KANTO_RADIO_GOT);
    default:
        return TRUE;
    }
}

static bool8 IsStationRocketProof(u8 station)
{
    // Location/region-locked stations are not hijacked by the Goldenrod takeover.
    switch (station)
    {
    case RADIO_STATION_UNOWN:
    case RADIO_STATION_EVOLUTION:
    case RADIO_STATION_PLACES_AND_PEOPLE:
    case RADIO_STATION_LETS_ALL_SING:
    case RADIO_STATION_POKE_FLUTE:
    case RADIO_STATION_HOENN_SOUND:
        return TRUE;
    default:
        return FALSE;
    }
}

static u8 FindStation(u8 tuningPos)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sRadioChannels); i++)
    {
        u8 station;

        if (sRadioChannels[i].tuningPos != tuningPos)
            continue;

        station = sRadioChannels[i].station;

        // The Pokemon Talk frequency carries the Pokedex Show in the morning.
        if (station == RADIO_STATION_POKEMON_TALK && GetTimeOfDay() == TIME_MORNING)
            station = RADIO_STATION_POKEDEX_SHOW;

        if (!IsStationAvailable(station))
            return RADIO_STATION_NONE;

        if (!IsStationRocketProof(station) && IsRocketTakeoverActive())
            return RADIO_STATION_ROCKET;
        return station;
    }

    return RADIO_STATION_NONE;
}

static const u8 *GetStationName(u8 station)
{
    u32 i;

    if (station == RADIO_STATION_NONE)
        return sText_NoStation;
    if (station == RADIO_STATION_ROCKET)
        return sText_TeamRocket;
    if (station == RADIO_STATION_POKEDEX_SHOW)
        return sText_PokedexShow;

    for (i = 0; i < ARRAY_COUNT(sRadioChannels); i++)
    {
        if (sRadioChannels[i].station == station)
            return sRadioChannels[i].name;
    }

    return sText_NoStation;
}

static u16 GetStationMusic(u8 station)
{
    switch (station)
    {
    case RADIO_STATION_POKEMON_TALK:
        return MUS_HG_RADIO_OAK;
    case RADIO_STATION_POKEMON_MUSIC:
        return GetDayOfWeek() % 2 == 0 ? MUS_HG_RADIO_MARCH : MUS_HG_RADIO_LULLABY;
    case RADIO_STATION_BUENAS_PASSWORD:
        return BuenasPassword_IsBroadcastTime() ? MUS_HG_RADIO_BUENA : 0;
    case RADIO_STATION_UNOWN:
        return MUS_HG_RADIO_UNOWN;
    case RADIO_STATION_ROCKET:
        return MUS_HG_RADIO_ROCKET;
    case RADIO_STATION_POKEDEX_SHOW:
    case RADIO_STATION_PLACES_AND_PEOPLE:
        return MUS_HG_RADIO_OAK;
    case RADIO_STATION_LUCKY_CHANNEL:
        return MUS_HG_RADIO_JINGLE;
    case RADIO_STATION_LETS_ALL_SING:
        return GetDayOfWeek() % 2 == 0 ? MUS_HG_RADIO_MARCH : MUS_HG_RADIO_LULLABY;
    case RADIO_STATION_POKE_FLUTE:
        return MUS_HG_RADIO_POKE_FLUTE;
    case RADIO_STATION_EVOLUTION:
        return MUS_HG_RADIO_ROCKET;
    case RADIO_STATION_HOENN_SOUND:
        return sHoennSoundSongs[Random() % ARRAY_COUNT(sHoennSoundSongs)];
    default:
        return 0;
    }
}

static void PrintStationName(u8 station)
{
    const u8 *name = GetStationName(station);
    u32 width = GetStringWidth(FONT_NORMAL, name, -1);
    u32 windowWidth = 19 * 8;

    FillWindowPixelBuffer(sRadio->stationNameWindowId, PIXEL_FILL(0));
    AddTextPrinterParameterized3(sRadio->stationNameWindowId,
                                 FONT_NORMAL,
                                 (windowWidth - width) / 2,
                                 1,
                                 sStationNameTextColors,
                                 TEXT_SKIP_DRAW,
                                 name);
    CopyWindowToVram(sRadio->stationNameWindowId, COPYWIN_FULL);
}

static void AddRadioLine(const u8 *text)
{
    if (sRadio->numLines < RADIO_MAX_LINES)
        sRadio->lines[sRadio->numLines++] = text;
}

// Each line index owns the buffer with the same index, so a line built
// at runtime is always written to topicLineBuffers[numLines].
static u8 *AllocRadioLineBuffer(void)
{
    if (sRadio->numLines >= RADIO_MAX_LINES)
        return NULL;
    return sRadio->topicLineBuffers[sRadio->numLines];
}

static void AppendRadioChar(u8 *buffer, u8 character)
{
    u8 *end = buffer + StringLength(buffer);

    *end++ = character;
    *end = EOS;
}

static void AddRadioNumberLine(u32 number)
{
    u8 *line = AllocRadioLineBuffer();

    if (line == NULL)
        return;
    ConvertIntToDecimalStringN(line, number, STR_CONV_MODE_LEADING_ZEROS, 5);
    AppendRadioChar(line, CHAR_EXCL_MARK);
    AddRadioLine(line);
}

static bool8 IsRadioBreakChar(u8 c)
{
    return c == CHAR_SPACE || c == CHAR_NEWLINE
        || c == CHAR_PROMPT_SCROLL || c == CHAR_PROMPT_CLEAR;
}

static const u8 *SkipRadioBreakChars(const u8 *text)
{
    while (*text != EOS && IsRadioBreakChar(*text))
        text++;
    return text;
}

// Word-wraps text to the radio window, one line buffer per line.
static void AddRadioWrappedText(const u8 *text)
{
    text = SkipRadioBreakChars(text);

    while (*text != EOS && sRadio->numLines < RADIO_MAX_LINES)
    {
        u8 *line = AllocRadioLineBuffer();
        u32 pos = 0;

        line[0] = EOS;
        while (*text != EOS)
        {
            const u8 *wordEnd = text;
            u32 wordLen, needSpace = (pos > 0) ? 1 : 0;

            while (*wordEnd != EOS && !IsRadioBreakChar(*wordEnd))
                wordEnd++;
            wordLen = wordEnd - text;

            if (pos + needSpace + wordLen >= RADIO_LINE_BUFFER_SIZE)
                break;
            if (needSpace)
                line[pos++] = CHAR_SPACE;
            memcpy(&line[pos], text, wordLen);
            pos += wordLen;
            line[pos] = EOS;

            if (GetStringWidth(FONT_NORMAL, line, -1) > RADIO_LINE_PIXEL_WIDTH)
            {
                pos -= wordLen + needSpace;
                line[pos] = EOS;
                break;
            }
            text = SkipRadioBreakChars(wordEnd);
        }

        if (pos == 0)
            break; // a single word wider than the window; give up
        AddRadioLine(line);
    }
}

static u32 GetLuckyNumber(void)
{
    if (!FlagGet(FLAG_DAILY_LUCKY_NUMBER_SET))
    {
        u32 number = (((u32)(Random() % 2) << 16) | Random()) % 100000;

        VarSet(VAR_RADIO_LUCKY_ID, number & 0xFFFF);
        VarSet(VAR_RADIO_LUCKY_ID_HI, number >> 16);
        FlagSet(FLAG_DAILY_LUCKY_NUMBER_SET);
    }
    return ((u32)VarGet(VAR_RADIO_LUCKY_ID_HI) << 16) | VarGet(VAR_RADIO_LUCKY_ID);
}

static void AddPokedexShowLines(void)
{
    enum NationalDexOrder natDex;
    u32 caughtCount = 0, pick, seen = 0;
    u16 species;

    for (natDex = 1; natDex <= NATIONAL_DEX_COUNT; natDex++)
    {
        if (GetSetPokedexFlag(natDex, FLAG_GET_CAUGHT))
            caughtCount++;
    }

    AddRadioLine(sText_PokedexShow1);
    if (caughtCount == 0)
    {
        AddRadioLine(sText_PokedexShowEmpty);
        return;
    }

    pick = Random() % caughtCount;
    for (natDex = 1; natDex <= NATIONAL_DEX_COUNT; natDex++)
    {
        if (GetSetPokedexFlag(natDex, FLAG_GET_CAUGHT))
        {
            if (seen == pick)
                break;
            seen++;
        }
    }

    species = NationalPokedexNumToSpecies(natDex);
    if (species != SPECIES_NONE)
    {
        u8 *line = AllocRadioLineBuffer();
        const u8 *description = GetSpeciesPokedexDescription(species);

        StringCopy(line, sText_PokedexShow2);
        StringAppend(line, GetSpeciesName(species));
        AppendRadioChar(line, CHAR_EXCL_MARK);
        AddRadioLine(line);
        if (description != NULL)
            AddRadioWrappedText(description);
    }
}

static bool8 IsPnPTrainerExcluded(u16 trainerId)
{
    switch (GetTrainerClassFromId(trainerId))
    {
    case TRAINER_CLASS_CHAMPION:
    case TRAINER_CLASS_ELITE_FOUR:
    case TRAINER_CLASS_LEADER:
    case TRAINER_CLASS_RIVAL:
        return TRUE;
    default:
        return GetTrainerNameFromId(trainerId)[0] == EOS
            || GetTrainerClassNameFromId(trainerId)[0] == EOS;
    }
}

static void AddPlacesAndPeopleLines(void)
{
    bool8 doPeople = Random() % 2 == 0;

    AddRadioLine(sText_PnP1);
    AddRadioLine(sText_PnP2);

    // Each entry takes two lines: the subject, then the adjective.
    while (sRadio->numLines + 2 <= RADIO_MAX_LINES)
    {
        u8 *line = AllocRadioLineBuffer();

        if (doPeople)
        {
            u32 tries;
            u16 trainerId = 0;

            for (tries = 0; tries < 32; tries++)
            {
                trainerId = (Random() % (TRAINERS_COUNT - 1)) + 1;
                if (!IsPnPTrainerExcluded(trainerId))
                    break;
            }
            if (tries == 32)
                doPeople = FALSE;
            else
            {
                StringCopy(line, GetTrainerClassNameFromId(trainerId));
                StringAppend(line, sText_Space);
                StringAppend(line, GetTrainerNameFromId(trainerId));
            }
        }
        if (!doPeople)
            GetMapName(line, sPnPPlaces[Random() % ARRAY_COUNT(sPnPPlaces)], 0);

        AddRadioLine(line);
        AddRadioLine(sPnPAdjectives[Random() % ARRAY_COUNT(sPnPAdjectives)]);

        if (Random() % 256 < 10)
            break;
        doPeople = Random() % 2 == 0;
    }
}

static void AddRadioTopic(const u8 *text)
{
    while (*text != EOS && sRadio->numLines < RADIO_MAX_LINES)
    {
        u32 length = 0;
        u8 *line = sRadio->topicLineBuffers[sRadio->numLines];

        while (*text != EOS
            && *text != CHAR_NEWLINE
            && *text != CHAR_PROMPT_SCROLL
            && *text != CHAR_PROMPT_CLEAR
            && *text != EXT_CTRL_CODE_BEGIN)
        {
            if (length < RADIO_LINE_BUFFER_SIZE - 1)
                line[length++] = *text;
            text++;
        }

        line[length] = EOS;
        if (length != 0)
            AddRadioLine(line);

        if (*text == CHAR_NEWLINE || *text == CHAR_PROMPT_SCROLL || *text == CHAR_PROMPT_CLEAR)
            text++;
        else if (*text == EXT_CTRL_CODE_BEGIN)
            break;
    }
}

static void GenerateStationContent(u8 station)
{
    sRadio->numLines = 0;

    switch (station)
    {
    case RADIO_STATION_POKEMON_TALK:
        AddRadioTopic(sOakTalkTopics[Random() % ARRAY_COUNT(sOakTalkTopics)]);
        break;
    case RADIO_STATION_POKEMON_MUSIC:
        AddRadioLine(sText_Music1);
        AddRadioLine(sText_Music2);
        AddRadioLine(GetDayOfWeek() % 2 == 0 ? sText_Music3March : sText_Music3Lullaby);
        break;
    case RADIO_STATION_LETS_ALL_SING:
        AddRadioLine(sText_Fern1);
        AddRadioLine(sText_Fern2);
        AddRadioLine(GetDayOfWeek() % 2 == 0 ? sText_Music3March : sText_Music3Lullaby);
        break;
    case RADIO_STATION_POKEDEX_SHOW:
        AddPokedexShowLines();
        break;
    case RADIO_STATION_LUCKY_CHANNEL:
    {
        u32 luckyNumber = GetLuckyNumber();

        AddRadioLine(sText_Lucky1);
        AddRadioLine(sText_Lucky2);
        AddRadioLine(sText_Lucky3);
        AddRadioLine(sText_Lucky4);
        AddRadioLine(sText_Lucky5);
        AddRadioNumberLine(luckyNumber);
        AddRadioLine(sText_LuckyRepeat);
        AddRadioLine(sText_Lucky5);
        AddRadioNumberLine(luckyNumber);
        AddRadioLine(sText_LuckyMatch);
        AddRadioLine(sText_LuckyTower);
        if (Random() % 2 == 0)
        {
            AddRadioLine(sText_LuckyDrag1);
            AddRadioLine(sText_LuckyDrag2);
        }
        break;
    }
    case RADIO_STATION_PLACES_AND_PEOPLE:
        AddPlacesAndPeopleLines();
        break;
    case RADIO_STATION_HOENN_SOUND:
        AddRadioLine(sText_Hoenn1);
        AddRadioLine(sText_Hoenn2);
        AddRadioLine(sText_Hoenn3);
        AddRadioLine(sText_Hoenn4);
        break;
    case RADIO_STATION_POKE_FLUTE:
    case RADIO_STATION_EVOLUTION:
        break; // music only, as in HnS
    case RADIO_STATION_BUENAS_PASSWORD:
        if (BuenasPassword_IsBroadcastTime())
        {
            BuenasPassword_BufferCurrentPassword();
            StringExpandPlaceholders(sRadio->lineBuffer, sText_BuenaPassword);
            AddRadioLine(sText_Buena1);
            AddRadioLine(sText_Buena2);
            AddRadioLine(sText_Buena3);
            AddRadioLine(sRadio->lineBuffer);
            AddRadioLine(sText_Buena4);
            AddRadioLine(sText_Buena5);
        }
        else
        {
            AddRadioLine(sText_BuenaOffAir1);
            AddRadioLine(sText_BuenaOffAir2);
        }
        break;
    case RADIO_STATION_UNOWN:
        AddRadioLine(sText_Unown1);
        AddRadioLine(sText_Unown2);
        break;
    case RADIO_STATION_ROCKET:
        AddRadioLine(sText_Rocket1);
        AddRadioLine(sText_Rocket2);
        AddRadioLine(sText_Rocket3);
        AddRadioLine(sText_Rocket4);
        AddRadioLine(sText_Rocket5);
        break;
    }

    sRadio->currentLine = 0;
    sRadio->scrollTimer = RADIO_SCROLL_DELAY;
    sRadio->needsScroll = FALSE;
}

static void PrintFirstRadioLine(void)
{
    FillWindowPixelBuffer(sRadio->radioTextWindowId, PIXEL_FILL(1));
    if (sRadio->numLines != 0)
    {
        AddTextPrinterParameterized3(sRadio->radioTextWindowId,
                                     FONT_NORMAL,
                                     2,
                                     RADIO_LINE_HEIGHT + 1,
                                     sRadioTextColors,
                                     TEXT_SKIP_DRAW,
                                     sRadio->lines[0]);
        sRadio->needsScroll = TRUE;
    }
    CopyWindowToVram(sRadio->radioTextWindowId, COPYWIN_GFX);
}

static void ScrollRadioText(void)
{
    if (sRadio->numLines == 0)
        return;

    if (sRadio->needsScroll)
        ScrollWindow(sRadio->radioTextWindowId, 0, RADIO_LINE_HEIGHT, PIXEL_FILL(1));
    else
        FillWindowPixelBuffer(sRadio->radioTextWindowId, PIXEL_FILL(1));

    AddTextPrinterParameterized3(sRadio->radioTextWindowId,
                                 FONT_NORMAL,
                                 2,
                                 RADIO_LINE_HEIGHT + 1,
                                 sRadioTextColors,
                                 TEXT_SKIP_DRAW,
                                 sRadio->lines[sRadio->currentLine]);
    CopyWindowToVram(sRadio->radioTextWindowId, COPYWIN_GFX);
    sRadio->needsScroll = TRUE;
}

static void UpdateTuning(void)
{
    u16 music;

    if (sRadio->dialSpriteId != MAX_SPRITES)
        gSprites[sRadio->dialSpriteId].x = RADIO_DIAL_BASE_X + sRadio->tuningPos;

    sRadio->currentStation = FindStation(sRadio->tuningPos);
    PrintStationName(sRadio->currentStation);
    GenerateStationContent(sRadio->currentStation);
    PrintFirstRadioLine();

    music = GetStationMusic(sRadio->currentStation);
    if (music == sRadio->currentMusic)
        return;

    if (music == 0)
        StopMapMusic();
    else
        PlayNewMapMusic(music);
    sRadio->currentMusic = music;
}

static void Task_PokegearRadioInput(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        sLastTuningPos = sRadio->tuningPos;
        if (sRadio->currentMusic == 0)
            PlayNewMapMusic(GetCurrLocationDefaultMusic());
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_ExitPokegearRadio;
        return;
    }

    if (JOY_HELD(DPAD_LEFT) || JOY_HELD(DPAD_RIGHT))
    {
        if (++sRadio->tuneDelay >= RADIO_TUNE_DELAY)
        {
            sRadio->tuneDelay = 0;
            if (JOY_HELD(DPAD_LEFT) && sRadio->tuningPos > RADIO_TUNING_MIN)
            {
                sRadio->tuningPos--;
                UpdateTuning();
                return;
            }
            if (JOY_HELD(DPAD_RIGHT) && sRadio->tuningPos < RADIO_TUNING_MAX)
            {
                sRadio->tuningPos++;
                UpdateTuning();
                return;
            }
        }
    }
    else
    {
        sRadio->tuneDelay = RADIO_TUNE_DELAY - 1;
    }

    if (sRadio->numLines > 1)
    {
        if (sRadio->scrollTimer != 0)
            sRadio->scrollTimer--;
        else
        {
            sRadio->scrollTimer = RADIO_SCROLL_DELAY;
            sRadio->currentLine = (sRadio->currentLine + 1) % sRadio->numLines;
            ScrollRadioText();
        }
    }
}

static void Task_ExitPokegearRadio(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        MainCallback callback = sRadio->savedCallback;

        FreePokegearRadioResources();
        DestroyTask(taskId);
        SetMainCallback2(callback);
    }
}

static void FreePokegearRadioResources(void)
{
    if (sRadio == NULL)
        return;

    if (sRadio->dialSpriteId != MAX_SPRITES)
        DestroySprite(&gSprites[sRadio->dialSpriteId]);
    FreeSpriteTilesByTag(TAG_RADIO_DIAL);
    FreeSpritePaletteByTag(PAL_TAG_RADIO_DIAL);
    FreeAllWindowBuffers();
    TRY_FREE_AND_SET_NULL(sRadio);
}

// Hoenn Sound: a Hoenn route theme is playing while the player is in Kanto.
bool8 IsHoennSoundPlaying(void)
{
    u16 music = GetCurrentMapMusic();
    u32 i;

    if (!IsPlayerInKanto())
        return FALSE;

    for (i = 0; i < ARRAY_COUNT(sHoennSoundSongs); i++)
    {
        if (music == sHoennSoundSongs[i])
            return TRUE;
    }
    return FALSE;
}

// Special: VAR_RESULT = 1 Poke Flute station playing (wakes Vermilion's
// Snorlax), 2 Hoenn Sound playing, 0 otherwise.
void CheckRadioStation(void)
{
    if (GetCurrentMapMusic() == MUS_HG_RADIO_POKE_FLUTE)
        gSpecialVar_Result = 1;
    else if (IsHoennSoundPlaying())
        gSpecialVar_Result = 2;
    else
        gSpecialVar_Result = 0;
}
