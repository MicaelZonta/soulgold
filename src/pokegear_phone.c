// Agenda do Pokégear (Match Call GSC): a lista de quem deu o número e a
// ligação. Quem fala é a mesma SelectMatchCallMessage que atende a ligação
// recebida no campo (src/match_call.c), então o telefone diz a mesma coisa
// ligando ou sendo ligado. Diário: .claude/merge_hns/match_call_gsc.md.
#include "global.h"
#include "battle_setup.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "match_call.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "pokegear_phone.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/rematches.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define PHONE_MAX_ENTRIES   REMATCH_SPECIAL_TRAINER_START
#define PHONE_VISIBLE_ROWS  5
#define PHONE_ROW_HEIGHT    16
// Mapa de tiles do BG1 (512 por bloco de char): lista 1-280, moldura 300-308,
// nome 320-367, ajuda 370-417. A moldura NAO pode cair dentro da faixa da
// lista, senao ela escreve por cima do texto (a janela tem 28x10 = 280 tiles).
#define PHONE_FRAME_BASE_TILE 300
#define PHONE_FRAME_PALETTE 4
#define PHONE_TEXT_PALETTE  5
#define PHONE_NAME_PALETTE  15

enum
{
    PHONE_MODE_LIST,
    PHONE_MODE_CALLING,   // texto rolando
    PHONE_MODE_CALL_DONE, // esperando desligar
};

struct PokegearPhoneResources
{
    MainCallback savedCallback;
    u8 gfxLoadState;
    u8 mode;
    u8 numEntries;
    u8 cursor;
    u8 scroll;
    u8 nameWindowId;
    u8 mainWindowId;
    u8 helpWindowId;
    u16 trainerIds[PHONE_MAX_ENTRIES];
    u8 rematchIdx[PHONE_MAX_ENTRIES];
    u16 bg1TilemapBuffer[BG_SCREEN_SIZE / 2];
    u16 bg2TilemapBuffer[BG_SCREEN_SIZE / 2];
};

static EWRAM_DATA struct PokegearPhoneResources *sPhone = NULL;
static EWRAM_DATA u8 sPhoneLastCursor = 0;

static void CB2_PokegearPhoneSetup(void);
static bool8 PokegearPhoneDoGfxSetup(void);
static void CB2_PokegearPhoneMain(void);
static void VBlankCB_PokegearPhone(void);
static void Task_PokegearPhoneInput(u8 taskId);
static void Task_ExitPokegearPhone(u8 taskId);
static void FreePokegearPhoneResources(void);
static void BuildPhoneList(void);
static bool8 TrainerHasNews(u8 entry);
static void PrintPhoneTitle(const u8 *text);
static void DrawPhoneList(void);
static void DrawHelpBar(const u8 *text);
static void StartPhoneCall(void);

static const u32 sPokegearBgTiles[] = INCBIN_U32("graphics/pokegear/tiles.4bpp.smol");
static const u16 sPokegearBgTilemap[] = INCBIN_U16("graphics/pokegear/tiles.bin");
static const u16 sPokegearBgPal[] = INCBIN_U16("graphics/pokegear/tiles.gbapal");
static const u32 sPokegearBgFemaleTiles[] = INCBIN_U32("graphics/pokegear/tiles_f.4bpp.smol");
static const u16 sPokegearBgFemaleTilemap[] = INCBIN_U16("graphics/pokegear/tiles_f.bin");
static const u16 sPokegearBgFemalePal[] = INCBIN_U16("graphics/pokegear/tiles_f.gbapal");

static const u8 sText_PhoneTitle[] = _("Phone");
static const u8 sText_NoNumbers[] = _("No numbers yet.");
static const u8 sText_NoNumbersHint[] = _("Beat a trainer and they may ask");
static const u8 sText_NoNumbersHint2[] = _("for your number.");
static const u8 sText_ListHelp[] = _("{A_BUTTON}Call  {B_BUTTON}Back");
static const u8 sText_CallHelp[] = _("{A_BUTTON}Hang up");
static const u8 sText_News[] = _("!");
static const u8 sText_Space[] = _(" ");

static const u8 sPhoneTitleColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY};
static const u8 sPhoneTextColors[] = {TEXT_COLOR_WHITE, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};

static const struct BgTemplate sPhoneBgTemplates[] =
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

static const struct WindowTemplate sPhoneWindowTemplates[] =
{
    { // nome / titulo
        .bg = 1,
        .tilemapLeft = 3,
        .tilemapTop = 2,
        .width = 24,
        .height = 2,
        .paletteNum = PHONE_NAME_PALETTE,
        .baseBlock = 320,
    },
    { // lista ou texto da ligacao
        .bg = 1,
        .tilemapLeft = 1,
        .tilemapTop = 5,
        .width = 28,
        .height = 10,
        .paletteNum = PHONE_TEXT_PALETTE,
        .baseBlock = 1,
    },
    { // barra de ajuda
        .bg = 1,
        .tilemapLeft = 3,
        .tilemapTop = 16,
        .width = 24,
        .height = 2,
        .paletteNum = PHONE_NAME_PALETTE,
        .baseBlock = 370,
    },
    DUMMY_WIN_TEMPLATE,
};

void OpenPokegearPhone(MainCallback callback)
{
    if (callback == NULL)
        callback = CB2_ReturnToField;

    sPhone = AllocZeroed(sizeof(*sPhone));
    if (sPhone == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sPhone->savedCallback = callback;
    sPhone->mode = PHONE_MODE_LIST;
    BuildPhoneList();
    if (sPhoneLastCursor < sPhone->numEntries)
        sPhone->cursor = sPhoneLastCursor;
    if (sPhone->cursor >= PHONE_VISIBLE_ROWS)
        sPhone->scroll = sPhone->cursor - (PHONE_VISIBLE_ROWS - 1);
    gMain.state = 0;
    SetMainCallback2(CB2_PokegearPhoneSetup);
}

// Quem deu o numero: a mesma faixa que o sorteio da ligacao usa (os indices
// abaixo de REMATCH_SPECIAL_TRAINER_START).
static void BuildPhoneList(void)
{
    u32 i;

    sPhone->numEntries = 0;
    for (i = 0; i < PHONE_MAX_ENTRIES; i++)
    {
        if (!TrainerIsMatchCallRegistered(i))
            continue;
        sPhone->rematchIdx[sPhone->numEntries] = i;
        sPhone->trainerIds[sPhone->numEntries] = gRematchTable[i].trainerIds[0];
        sPhone->numEntries++;
    }
}

// "!" na lista: ele quer revanche ou guardou um item (as duas coisas que a
// ligacao recebida marca).
static bool8 TrainerHasNews(u8 entry)
{
    if (GetActiveTrainerRematches(sPhone->rematchIdx[entry]) != 0)
        return TRUE;

    return DoesPhoneTrainerHaveItem(sPhone->trainerIds[entry]);
}

static void CB2_PokegearPhoneSetup(void)
{
    while (TRUE)
    {
        if (PokegearPhoneDoGfxSetup())
            break;
    }
}

static bool8 PokegearPhoneDoGfxSetup(void)
{
    const u32 *bgTiles;
    const u16 *bgTilemap;
    const u16 *bgPal;

    if (gSaveBlock2Ptr->playerGender == MALE)
    {
        bgTiles = sPokegearBgTiles;
        bgTilemap = sPokegearBgTilemap;
        bgPal = sPokegearBgPal;
    }
    else
    {
        bgTiles = sPokegearBgFemaleTiles;
        bgTilemap = sPokegearBgFemaleTilemap;
        bgPal = sPokegearBgFemalePal;
    }

    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
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
        InitBgsFromTemplates(0, sPhoneBgTemplates, ARRAY_COUNT(sPhoneBgTemplates));
        SetBgTilemapBuffer(1, sPhone->bg1TilemapBuffer);
        SetBgTilemapBuffer(2, sPhone->bg2TilemapBuffer);
        FillBgTilemapBufferRect(1, 0, 0, 0, 32, 32, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        gMain.state++;
        break;
    case 3:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, bgTiles, 0, 0, 0);
        CopyToBgTilemapBufferRect(2, bgTilemap, 0, 0, 30, 20);
        LoadPalette(bgPal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 4:
        if (FreeTempTileDataBuffersIfPossible())
            break;
        InitWindows(sPhoneWindowTemplates);
        DeactivateAllTextPrinters();
        sPhone->nameWindowId = 0;
        sPhone->mainWindowId = 1;
        sPhone->helpWindowId = 2;
        LoadPalette(gStandardMenuPalette, BG_PLTT_ID(PHONE_TEXT_PALETTE), PLTT_SIZE_4BPP);
        Menu_LoadStdPalAt(BG_PLTT_ID(PHONE_NAME_PALETTE));
        LoadUserWindowBorderGfx(sPhone->mainWindowId, PHONE_FRAME_BASE_TILE, BG_PLTT_ID(PHONE_FRAME_PALETTE));
        DrawStdFrameWithCustomTileAndPalette(sPhone->mainWindowId, FALSE, PHONE_FRAME_BASE_TILE, PHONE_FRAME_PALETTE);
        PutWindowTilemap(sPhone->nameWindowId);
        PutWindowTilemap(sPhone->mainWindowId);
        PutWindowTilemap(sPhone->helpWindowId);
        PrintPhoneTitle(sText_PhoneTitle);
        DrawPhoneList();
        DrawHelpBar(sText_ListHelp);
        ScheduleBgCopyTilemapToVram(1);
        ScheduleBgCopyTilemapToVram(2);
        ShowBg(1);
        ShowBg(2);
        CreateTask(Task_PokegearPhoneInput, 0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_PokegearPhone);
        SetMainCallback2(CB2_PokegearPhoneMain);
        return TRUE;
    }

    return FALSE;
}

static void CB2_PokegearPhoneMain(void)
{
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_PokegearPhone(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void PrintPhoneTitle(const u8 *text)
{
    FillWindowPixelBuffer(sPhone->nameWindowId, PIXEL_FILL(0));
    AddTextPrinterParameterized3(sPhone->nameWindowId, FONT_NORMAL, 0, 1,
                                 sPhoneTitleColors, TEXT_SKIP_DRAW, text);
    CopyWindowToVram(sPhone->nameWindowId, COPYWIN_FULL);
}

static void DrawHelpBar(const u8 *text)
{
    FillWindowPixelBuffer(sPhone->helpWindowId, PIXEL_FILL(0));
    AddTextPrinterParameterized3(sPhone->helpWindowId, FONT_SMALL, 0, 1,
                                 sPhoneTitleColors, TEXT_SKIP_DRAW, text);
    CopyWindowToVram(sPhone->helpWindowId, COPYWIN_FULL);
}

static void DrawPhoneList(void)
{
    u32 i;

    FillWindowPixelBuffer(sPhone->mainWindowId, PIXEL_FILL(1));

    if (sPhone->numEntries == 0)
    {
        AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_NORMAL, 8, 8,
                                     sPhoneTextColors, TEXT_SKIP_DRAW, sText_NoNumbers);
        AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_SMALL, 8, 32,
                                     sPhoneTextColors, TEXT_SKIP_DRAW, sText_NoNumbersHint);
        AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_SMALL, 8, 46,
                                     sPhoneTextColors, TEXT_SKIP_DRAW, sText_NoNumbersHint2);
        CopyWindowToVram(sPhone->mainWindowId, COPYWIN_FULL);
        return;
    }

    for (i = 0; i < PHONE_VISIBLE_ROWS; i++)
    {
        u32 entry = sPhone->scroll + i;
        u16 trainerId;
        u32 y = i * PHONE_ROW_HEIGHT + 2;

        if (entry >= sPhone->numEntries)
            break;

        trainerId = sPhone->trainerIds[entry];
        if (entry == sPhone->cursor)
            AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_NORMAL, 0, y,
                                         sPhoneTextColors, TEXT_SKIP_DRAW, gText_SelectorArrow);

        StringCopy(gStringVar4, GetTrainerClassNameFromId(trainerId));
        StringAppend(gStringVar4, sText_Space);
        StringAppend(gStringVar4, GetTrainerNameFromId(trainerId));
        AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_NORMAL, 10, y,
                                     sPhoneTextColors, TEXT_SKIP_DRAW, gStringVar4);

        if (TrainerHasNews(entry))
            AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_NORMAL, 200, y,
                                         sPhoneTextColors, TEXT_SKIP_DRAW, sText_News);
    }
    CopyWindowToVram(sPhone->mainWindowId, COPYWIN_FULL);
}

static void StartPhoneCall(void)
{
    u16 trainerId = sPhone->trainerIds[sPhone->cursor];

    PlaySE(SE_POKENAV_CALL);
    PrintPhoneTitle(GetTrainerNameFromId(trainerId));
    // A mesma fala da ligacao recebida. Nao mexe em estado: quem marca
    // revanche e a ligacao de rota (src/match_call.c).
    SelectMatchCallMessage(trainerId, gStringVar4);
    FillWindowPixelBuffer(sPhone->mainWindowId, PIXEL_FILL(1));
    // Limpa a lista antes de o printer comecar: ele so copia o que desenha.
    CopyWindowToVram(sPhone->mainWindowId, COPYWIN_GFX);
    AddTextPrinterParameterized3(sPhone->mainWindowId, FONT_NORMAL, 2, 2,
                                 sPhoneTextColors, GetPlayerTextSpeedDelay(), gStringVar4);
    DrawHelpBar(sText_CallHelp);
    sPhone->mode = PHONE_MODE_CALLING;
}

static void Task_PokegearPhoneInput(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    switch (sPhone->mode)
    {
    case PHONE_MODE_LIST:
        if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            sPhoneLastCursor = sPhone->cursor;
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_ExitPokegearPhone;
            return;
        }
        if (JOY_NEW(A_BUTTON) && sPhone->numEntries != 0)
        {
            StartPhoneCall();
            return;
        }
        if (JOY_REPEAT(DPAD_UP) && sPhone->cursor != 0)
        {
            PlaySE(SE_SELECT);
            sPhone->cursor--;
            if (sPhone->cursor < sPhone->scroll)
                sPhone->scroll = sPhone->cursor;
            DrawPhoneList();
            return;
        }
        if (JOY_REPEAT(DPAD_DOWN) && sPhone->cursor + 1 < sPhone->numEntries)
        {
            PlaySE(SE_SELECT);
            sPhone->cursor++;
            if (sPhone->cursor >= sPhone->scroll + PHONE_VISIBLE_ROWS)
                sPhone->scroll = sPhone->cursor - (PHONE_VISIBLE_ROWS - 1);
            DrawPhoneList();
            return;
        }
        break;
    case PHONE_MODE_CALLING:
        // O proprio printer trata \p (espera o A e limpa a janela).
        if (!IsTextPrinterActiveOnWindow(sPhone->mainWindowId))
            sPhone->mode = PHONE_MODE_CALL_DONE;
        break;
    case PHONE_MODE_CALL_DONE:
        if (JOY_NEW(A_BUTTON | B_BUTTON))
        {
            PlaySE(SE_POKENAV_HANG_UP);
            PrintPhoneTitle(sText_PhoneTitle);
            DrawPhoneList();
            DrawHelpBar(sText_ListHelp);
            sPhone->mode = PHONE_MODE_LIST;
        }
        break;
    }
}

static void Task_ExitPokegearPhone(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        MainCallback callback = sPhone->savedCallback;

        FreePokegearPhoneResources();
        DestroyTask(taskId);
        SetMainCallback2(callback);
    }
}

static void FreePokegearPhoneResources(void)
{
    if (sPhone == NULL)
        return;

    FreeAllWindowBuffers();
    TRY_FREE_AND_SET_NULL(sPhone);
}
