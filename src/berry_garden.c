// Berry Master's garden on Route 30.
//
// Design:  .claude/berry_master/REI_DA_COLHEITA.md
// Plan:    .claude/berry_master/PLANO_DE_IMPLEMENTACAO.md
//
// This file holds the RULES; the flow (who says what, when) is the map script
// of Route30 and Route30_House, which only asks questions through the specials
// below.

#include "global.h"
#include "berry.h"
#include "berry_garden.h"
#include "clock.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_screen_effect.h"
#include "item.h"
#include "level_scaling.h"
#include "list_menu.h"
#include "malloc.h"
#include "money.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "rtc.h"
#include "script_menu.h"
#include "string_util.h"
#include "wild_encounter.h"
#include "constants/berry.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/vars.h"

// ---------------------------------------------------------------------------
// Book of Berries (section 3)
//
// One flag per Berry, contiguous and in item order, so the flag of a Berry is
// a sum and needs no table. The e-Reader Enigma has no entry.
// ---------------------------------------------------------------------------

#define LEDGER_FIRST_ITEM  FIRST_BERRY_INDEX
#define LEDGER_LAST_ITEM   ITEM_MARANGA_BERRY
#define LEDGER_SIZE        (LEDGER_LAST_ITEM - LEDGER_FIRST_ITEM + 1)

STATIC_ASSERT(FLAG_BERRY_LEDGER_END - FLAG_BERRY_LEDGER_START + 1 == LEDGER_SIZE, BerryLedgerFlagsMatchBerries);

// The eight Berries Bram has always grown: in the Book from the tutorial on.
static const u16 sStarterBerries[] =
{
    ITEM_CHERI_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_PECHA_BERRY,
    ITEM_RAWST_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_LEPPA_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_PERSIM_BERRY,
};

// Book size -> prize, paid once each by Bram (section 3.4). 66 (every Berry
// but the Enigma) is the title, not an item: it belongs to the epilogue scene
// (part 16) and is deliberately not in this list. Careful there: the Enigma
// DOES count in BerryLedger_Count, so "66 in the Book" is not "complete but
// the Enigma" - part 16 has to check every Berry except the Enigma instead.
static const u8 sMilestones[] = {12, 20, 30, 40, 50, 60};

static bool32 IsInLedger(u16 itemId)
{
    return itemId >= LEDGER_FIRST_ITEM && itemId <= LEDGER_LAST_ITEM;
}

bool32 BerryLedger_Has(u16 itemId)
{
    if (!IsInLedger(itemId))
        return FALSE;
    return FlagGet(FLAG_BERRY_LEDGER_START + (itemId - LEDGER_FIRST_ITEM));
}

void BerryLedger_RegisterItem(u16 itemId)
{
    if (IsInLedger(itemId))
        FlagSet(FLAG_BERRY_LEDGER_START + (itemId - LEDGER_FIRST_ITEM));
}

// Lansat and Starf only cross after the League, and the Enigma has no source
// but Laurel's plot: none of them is ever handed out by the daily draw.
static bool32 IsDailyGiftBerry(u16 itemId)
{
    return itemId != ITEM_LANSAT_BERRY
        && itemId != ITEM_STARF_BERRY
        && itemId != ITEM_ENIGMA_BERRY;
}

static bool32 IsRareGiftBerry(u16 itemId)
{
    return itemId >= FIRST_BERRY_MASTER_RARE
        && itemId <= LAST_BERRY_MASTER_RARE
        && itemId != ITEM_ENIGMA_BERRY;
}

// Uniform draw among the registered Berries that pass the filter.
static u16 RandomRegistered(bool32 (*filter)(u16 itemId))
{
    u32 itemId, count = 0, pick;

    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
    {
        if (BerryLedger_Has(itemId) && filter(itemId))
            count++;
    }
    if (count == 0)
        return ITEM_NONE;

    pick = Random() % count;
    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
    {
        if (BerryLedger_Has(itemId) && filter(itemId) && pick-- == 0)
            break;
    }
    return itemId;
}

// VAR_0x8004 = item
void BerryLedger_Register(void)
{
    BerryLedger_RegisterItem(gSpecialVar_0x8004);
}

// Safe to call any number of times: also fills the Book of a save that did
// the tutorial before the Book existed.
void BerryLedger_RegisterStarters(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sStarterBerries); i++)
        BerryLedger_RegisterItem(sStarterBerries[i]);
}

u16 BerryLedger_Count(void)
{
    u32 itemId, count = 0;

    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
    {
        if (BerryLedger_Has(itemId))
            count++;
    }
    return count;
}

// Bram's daily gift: ITEM_NONE only when the Book is empty.
u16 BerryLedger_RandomRegistered(void)
{
    return RandomRegistered(IsDailyGiftBerry);
}

// Laurel's daily rare (post-League): ITEM_NONE when no rare is in the Book.
u16 BerryLedger_RandomRegisteredRare(void)
{
    return RandomRegistered(IsRareGiftBerry);
}

// The smallest milestone the Book has reached that Bram has not paid yet
// (VAR_BERRY_LEDGER_MILESTONE holds the last one paid), or 0. The script pays
// it and writes it back, so an old save with a big Book is paid one prize
// after the other, in order.
u16 BerryLedger_PendingMilestone(void)
{
    u32 i, count = BerryLedger_Count();
    u16 paid = VarGet(VAR_BERRY_LEDGER_MILESTONE);

    for (i = 0; i < ARRAY_COUNT(sMilestones); i++)
    {
        if (sMilestones[i] > paid && sMilestones[i] <= count)
            return sMilestones[i];
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Daily state (section 14.6)
//
// One daily flag and one var of bits, like Kurt (VAR_KURT_TODAY) and the
// Nexus (VAR_NEXUS_DAILY). ClearDailyFlags clears FLAG_DAILY_GARDEN_NEW_DAY at
// the date change; the first GardenRollDay of the new day finds it clear and
// starts the day over. Nothing stores a date and nothing polls the clock.
//
// Who calls GardenRollDay: the ON_TRANSITION of Route30 and Route30_House
// (the date check runs before it on every map load), AND the start of every
// garden conversation, after dotimebasedevents - midnight can pass while the
// player stands on Route 30, and then no map load happens.
// ---------------------------------------------------------------------------

STATIC_ASSERT(GARDEN_TODAY_BIT_COUNT <= 16, GardenTodayFitsInAVar);

bool32 GardenToday_Has(u32 bit)
{
    if (bit >= GARDEN_TODAY_BIT_COUNT)
        return FALSE;
    return (VarGet(VAR_GARDEN_TODAY) >> bit) & 1;
}

void GardenToday_Mark(u32 bit)
{
    if (bit < GARDEN_TODAY_BIT_COUNT)
        VarSet(VAR_GARDEN_TODAY, VarGet(VAR_GARDEN_TODAY) | (1 << bit));
}

static void FinishGardenWork(void);

#define KLARA_ONE_IN  7   // mornings (section 14.3)

void GardenRollDay(void)
{
    if (FlagGet(FLAG_DAILY_GARDEN_NEW_DAY))
        return;

    VarSet(VAR_GARDEN_TODAY, 0);
    FlagSet(FLAG_DAILY_GARDEN_NEW_DAY);
    FinishGardenWork();

    // The day's draws, once each:
    //   Mustard, 1 Sunday in 4, story state 15 (part 16)          -> GARDEN_TODAY_MUSTARD_COMES
    if (VarGet(VAR_BERRY_GARDEN_LEVEL) >= GARDEN_LEVEL_PROPER && Random() % KLARA_ONE_IN == 0)
        GardenToday_Mark(GARDEN_TODAY_KLARA_COMES);
}

// VAR_0x8004 = GARDEN_TODAY_* bit
u16 GardenToday_Check(void)
{
    return GardenToday_Has(gSpecialVar_0x8004);
}

// VAR_0x8004 = GARDEN_TODAY_* bit
void GardenToday_Set(void)
{
    GardenToday_Mark(gSpecialVar_0x8004);
}

// ---------------------------------------------------------------------------
// Garden levels (section 5)
//
// Bram offers the next level once the Book is big enough; the player pays and
// the work is done overnight: the payment always comes after today's
// GardenRollDay (every garden conversation calls it first), so the first
// GardenRollDay that can finish it is tomorrow's. Bram talks about it the next
// time the player sees him (GardenReform_TakeBuiltLevel).
// ---------------------------------------------------------------------------

struct GardenReform
{
    u8 bookSize;
    bool8 needsAct1;
    u16 price;
};

static const struct GardenReform sGardenReforms[] =
{
    [GARDEN_LEVEL_PROPER]    = { .bookSize = 12, .needsAct1 = FALSE, .price = 5000 },
    [GARDEN_LEVEL_CHANNEL]   = { .bookSize = 22, .needsAct1 = TRUE,  .price = 10000 },
    [GARDEN_LEVEL_BUG_HOTEL] = { .bookSize = 32, .needsAct1 = TRUE,  .price = 0 }, // Bugsy builds it
};

STATIC_ASSERT(ARRAY_COUNT(sGardenReforms) == GARDEN_LEVEL_LAST_REFORM + 1, GardenReformsCoverEveryLevel);

static void FinishGardenWork(void)
{
    u16 work = VarGet(VAR_BERRY_GARDEN_WORK);

    if (work >= GARDEN_LEVEL_PROPER && work <= GARDEN_LEVEL_LAST_REFORM)
    {
        VarSet(VAR_BERRY_GARDEN_LEVEL, work);
        VarSet(VAR_BERRY_GARDEN_WORK, work + GARDEN_WORK_BUILT);
    }
}

// Returns GARDEN_REFORM_*; VAR_0x8005 = the level it is about.
u16 GardenReform_Check(void)
{
    u16 level = VarGet(VAR_BERRY_GARDEN_LEVEL);
    u16 work = VarGet(VAR_BERRY_GARDEN_WORK);
    u16 next = level + 1;

    gSpecialVar_0x8005 = next;
    if (work != GARDEN_WORK_NONE && work < GARDEN_WORK_BUILT)
    {
        gSpecialVar_0x8005 = work;
        return GARDEN_REFORM_BUILDING;
    }
    if (level < GARDEN_LEVEL_BACKYARD || next > GARDEN_LEVEL_LAST_REFORM)
        return GARDEN_REFORM_NONE;
    if (BerryLedger_Count() < sGardenReforms[next].bookSize)
        return GARDEN_REFORM_NONE;
    if (sGardenReforms[next].needsAct1 && VarGet(VAR_HARVEST_KING) < HARVEST_KING_ACT1_DONE)
        return GARDEN_REFORM_NEEDS_HELP;
    return GARDEN_REFORM_READY;
}

// Pays for the next level (only after GardenReform_Check said READY).
// Returns FALSE, and charges nothing, if the money is short.
u16 GardenReform_Pay(void)
{
    u16 next = VarGet(VAR_BERRY_GARDEN_LEVEL) + 1;

    if (GardenReform_Check() != GARDEN_REFORM_READY)
        return FALSE;
    if (!IsEnoughMoney(&gSaveBlock1Ptr->money, sGardenReforms[next].price))
        return FALSE;
    RemoveMoney(&gSaveBlock1Ptr->money, sGardenReforms[next].price);
    VarSet(VAR_BERRY_GARDEN_WORK, next);
    return TRUE;
}

// The level built overnight that Bram has not talked about yet, or 0; once
// asked, it is his to say and is cleared.
u16 GardenReform_TakeBuiltLevel(void)
{
    u16 work = VarGet(VAR_BERRY_GARDEN_WORK);

    if (work <= GARDEN_WORK_BUILT)
        return 0;
    VarSet(VAR_BERRY_GARDEN_WORK, GARDEN_WORK_NONE);
    return work - GARDEN_WORK_BUILT;
}

// Level 3, the channel: once a day, on entering Route 30, every garden plot
// gets watered for the stage it is in - the same as one Squirtbottle pass.
// Laurel's plot is not part of the garden (see BERRY_TREE_GARDEN_LAST).
void GardenIrrigate(void)
{
    u32 id;

    if (VarGet(VAR_BERRY_GARDEN_LEVEL) < GARDEN_LEVEL_CHANNEL || GardenToday_Has(GARDEN_TODAY_WATERED))
        return;
    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
        WaterBerryTreeById(id);
    GardenToday_Mark(GARDEN_TODAY_WATERED);
}

// Bram's gift: 2 Berries, 3 from level 2 on.
u16 GardenGift_Count(void)
{
    return VarGet(VAR_BERRY_GARDEN_LEVEL) >= GARDEN_LEVEL_PROPER ? 3 : 2;
}

// ---------------------------------------------------------------------------
// Seed order (section 3.5): from level 2, once a day and instead of the draw,
// the player names any Berry in the Book (not the Enigma, which is Laurel's
// plot's alone). The list is pushed onto the dynamic multichoice stack and
// shown by `dynmultistack` in the script; the id of each row is the item.
// The menu Free()s every row name when it closes, so each name is a heap
// copy, exactly like the dynmultipush command makes.
// ---------------------------------------------------------------------------

void BerryLedger_BuildSeedMenu(void)
{
    u32 itemId;

    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
    {
        struct ListMenuItem row;
        u8 *name;

        if (!BerryLedger_Has(itemId) || itemId == ITEM_ENIGMA_BERRY)
            continue;
        name = Alloc(ITEM_NAME_LENGTH + 1);
        CopyItemName(itemId, name);
        row.name = name;
        row.id = itemId;
        MultichoiceDynamic_PushElement(row);
    }
}

// ---------------------------------------------------------------------------
// Debug menu (Berry Master..., src/debug.c; scripts in data/scripts/debug.inc)
//
// Only the debug scripts call these. They change the save the same way the
// game would, so what they set up is what a player could reach.
// ---------------------------------------------------------------------------

// VAR_0x8004 = hours to move the clock FORWARD (the game's clock never goes
// back: VAR_DAYS would stop matching). Works on the real RTC: it rewrites the
// save's local time offset, like setting the wall clock. Crossing midnight
// clears the daily flags, and the Berry trees grow for the hours skipped, on
// the next map load (BerryDebug_ReloadMap).
void BerryDebug_AdvanceHours(void)
{
    s32 days, hours;

    RtcCalcLocalTime();
    hours = gLocalTime.hours + gSpecialVar_0x8004;
    days = gLocalTime.days + hours / 24;
    hours %= 24;
    RtcCalcLocalTimeOffset(days, hours, gLocalTime.minutes, gLocalTime.seconds);
    RtcCalcLocalTime();
}

// Forward to the next 07:00 (morning in the garden): today's if it is still
// before 7, else tomorrow's.
void BerryDebug_AdvanceToMorning(void)
{
    s32 days;

    RtcCalcLocalTime();
    days = gLocalTime.days;
    if (gLocalTime.hours >= 7)
        days++;
    RtcCalcLocalTimeOffset(days, 7, 0, 0);
    RtcCalcLocalTime();
}

// Warps to where the player stands, so the map scripts run again (time of
// day, GardenRollDay, the garden's visibility). The script must `waitstate`.
void BerryDebug_ReloadMap(void)
{
    SetWarpDestination(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum,
                       WARP_ID_NONE, gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y);
    DoWarp();
    ResetInitialPlayerAvatarState();
}

// VAR_0x8004 = Book size: Bram's eight first, then the others in item order,
// the Enigma only when the size asks for every Berry (67).
void BerryDebug_SetBook(void)
{
    u32 itemId, want = gSpecialVar_0x8004;

    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
        FlagClear(FLAG_BERRY_LEDGER_START + (itemId - LEDGER_FIRST_ITEM));
    if (want == 0)
        return;
    BerryLedger_RegisterStarters();
    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM && BerryLedger_Count() < want; itemId++)
    {
        if (itemId == ITEM_ENIGMA_BERRY && want < LEDGER_SIZE)
            continue;
        BerryLedger_RegisterItem(itemId);
    }
}

// VAR_0x8004 = level; any work in progress is dropped.
void BerryDebug_SetLevel(void)
{
    VarSet(VAR_BERRY_GARDEN_LEVEL, gSpecialVar_0x8004);
    VarSet(VAR_BERRY_GARDEN_WORK, GARDEN_WORK_NONE);
}

// The 10 garden plots (not Laurel's): every planted one jumps to ripe.
void BerryDebug_RipenGarden(void)
{
    u32 id;

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        struct BerryTree *tree = GetBerryTreeInfo(id);
        if (tree->stage != BERRY_STAGE_NO_BERRY && tree->stage != BERRY_STAGE_BERRIES)
        {
            tree->stage = BERRY_STAGE_BERRIES - 1;
            BerryTreeGrow(tree);
        }
    }
}

void BerryDebug_GrowGarden(void)
{
    u32 id;

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        struct BerryTree *tree = GetBerryTreeInfo(id);
        if (tree->stage != BERRY_STAGE_NO_BERRY && tree->stage != BERRY_STAGE_BERRIES)
            BerryTreeGrow(tree);
    }
}

void BerryDebug_EmptyGarden(void)
{
    u32 id;

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_KINGS_PLOT; id++)
        RemoveBerryTree(id);
}

// Today's gifts and the garden's day again, without touching the clock.
void BerryDebug_ResetToday(void)
{
    FlagClear(FLAG_DAILY_GARDEN_NEW_DAY);
    FlagClear(FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY);
    FlagClear(FLAG_DAILY_BERRY_MASTERS_WIFE);
    GardenRollDay();
}

// So "not enough money" can be tested on demand.
void BerryDebug_ClearMoney(void)
{
    SetMoney(&gSaveBlock1Ptr->money, 0);
}

// Back to a save that never met Bram: no tutorial, empty Book and garden.
void BerryDebug_ResetAll(void)
{
    gSpecialVar_0x8004 = 0;
    BerryDebug_SetBook();
    BerryDebug_EmptyGarden();
    FlagClear(FLAG_GOT_BERRY_ROUTE_30_HOUSE);
    VarSet(VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_NONE);
    VarSet(VAR_BERRY_GARDEN_WORK, GARDEN_WORK_NONE);
    VarSet(VAR_BERRY_LEDGER_MILESTONE, 0);
    VarSet(VAR_GARDEN_HEARTS, 0);
    VarSet(VAR_GARDEN_RIVALS, 0);
    VarSet(VAR_GARDEN_NEWS, 0);
    VarSet(VAR_BERRY_ORDER, 0);
    VarSet(VAR_HARVEST_KING, 0);
    BerryDebug_ResetToday();
}

// For the status screen: VAR_0x8004 = the Book, VAR_0x8005 = pending milestone,
// VAR_0x8006 = the local hour, VAR_0x8007 = how many garden plots are planted,
// VAR_0x8008..0x800A = Bram's, Laurel's and Tilly's hearts.
void BerryDebug_Status(void)
{
    RtcCalcLocalTime();
    gSpecialVar_0x8004 = BerryLedger_Count();
    gSpecialVar_0x8005 = BerryLedger_PendingMilestone();
    gSpecialVar_0x8006 = gLocalTime.hours;
    gSpecialVar_0x8007 = GardenPlots_Planted();
    gSpecialVar_0x8008 = GardenHearts_Get(GARDEN_HEARTS_BRAM);
    gSpecialVar_0x8009 = GardenHearts_Get(GARDEN_HEARTS_LAUREL);
    gSpecialVar_0x800A = GardenHearts_Get(GARDEN_HEARTS_TILLY);
}

// ---------------------------------------------------------------------------
// Today's order (section 6)
//
// One a day, drawn in the first conversation with Bram (GARDEN_TODAY_ORDER_ROLLED)
// and kept until the date changes, so walking out and in never redraws it.
//   common:    N of a Berry already in the Book
//   discovery: (garden level 2+, 1 day in 3) ONE Berry not in the Book whose two
//              parents are; Bram does not know the recipe, Laurel does
// The order lives in VAR_BERRY_ORDER: bits 0-6 Berry (offset + 1, 0 = none),
// 7-10 how many, 11 discovery, 12-15 client.
// How many and the pay come from the Berry's generation (section 4.2): the
// further from Bram's eight, the fewer asked and the better paid. Never a
// Poke Ball (Kurt is the only maker).
// ---------------------------------------------------------------------------

#define ORDER_BERRY_MASK     0x007F
#define ORDER_COUNT_SHIFT    7
#define ORDER_COUNT_MASK     0x0780
#define ORDER_DISCOVERY      0x0800
#define ORDER_CLIENT_SHIFT   12

#define DISCOVERY_ONE_IN     3
#define MAX_GENERATION       7

// By generation 0..7: how many a common order asks for, and the pay per Berry.
static const u8 sOrderCountByGeneration[MAX_GENERATION + 1] = {3, 5, 5, 3, 3, 1, 1, 1};
static const u16 sOrderPayByGeneration[MAX_GENERATION + 1]  = {100, 150, 200, 300, 400, 600, 800, 1000};

static bool32 IsStarterBerry(u16 itemId)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sStarterBerries); i++)
    {
        if (sStarterBerries[i] == itemId)
            return TRUE;
    }
    return FALSE;
}

// Crosses between this Berry and Bram's eight. The table has no cycles
// (dev_scripts/berry_mutations_check.py), so the recursion ends; a Berry
// with no recipe that is not a starter (the Enigma) counts as the deepest.
static u32 GetBerryGeneration(u16 itemId)
{
    u16 parent1, parent2;
    u32 gen1, gen2;

    if (IsStarterBerry(itemId))
        return 0;
    if (!GetBerryRecipe(itemId, &parent1, &parent2))
        return MAX_GENERATION;
    gen1 = GetBerryGeneration(parent1);
    gen2 = GetBerryGeneration(parent2);
    return min(MAX_GENERATION, max(gen1, gen2) + 1);
}

// A Berry not in the Book whose two parents are (and whose recipe is open:
// no Lansat or Starf before the League), drawn at random; ITEM_NONE if there
// is none. VAR_0x8005 / VAR_0x8006 = the parents.
static u16 NextDiscovery(u16 *parent1, u16 *parent2)
{
    u32 itemId, count = 0, pick;
    u16 p1, p2;

    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
    {
        if (!BerryLedger_Has(itemId) && GetBerryRecipe(itemId, &p1, &p2)
         && BerryLedger_Has(p1) && BerryLedger_Has(p2))
            count++;
    }
    if (count == 0)
        return ITEM_NONE;
    pick = Random() % count;
    for (itemId = LEDGER_FIRST_ITEM; itemId <= LEDGER_LAST_ITEM; itemId++)
    {
        if (!BerryLedger_Has(itemId) && GetBerryRecipe(itemId, &p1, &p2)
         && BerryLedger_Has(p1) && BerryLedger_Has(p2) && pick-- == 0)
        {
            *parent1 = p1;
            *parent2 = p2;
            return itemId;
        }
    }
    return ITEM_NONE;
}

u16 BerryLedger_NextDiscovery(void)
{
    u16 parent1 = ITEM_NONE, parent2 = ITEM_NONE;
    u16 itemId = NextDiscovery(&parent1, &parent2);

    gSpecialVar_0x8005 = parent1;
    gSpecialVar_0x8006 = parent2;
    return itemId;
}

// VAR_0x8004 = Berry -> VAR_0x8005 / VAR_0x8006 = its parents; FALSE if none.
u16 BerryLedger_GetRecipe(void)
{
    u16 parent1, parent2;

    if (!GetBerryRecipe(gSpecialVar_0x8004, &parent1, &parent2))
        return FALSE;
    gSpecialVar_0x8005 = parent1;
    gSpecialVar_0x8006 = parent2;
    return TRUE;
}

static u16 PickClient(void)
{
    u16 client = Random() % GARDEN_CLIENT_COUNT;

    if (client == GARDEN_CLIENT_BUGSY && VarGet(VAR_HARVEST_KING) < HARVEST_KING_BUGSY_CAME)
        client = GARDEN_CLIENT_KURT;
    return client;
}

enum OrderKind
{
    ORDER_KIND_RANDOM,      // the game: discovery 1 day in 3 from level 2
    ORDER_KIND_COMMON,      // debug menu
    ORDER_KIND_DISCOVERY,   // debug menu (falls back to common if none is possible)
};

// Debug menu only (BerryDebug_NewOrder); RAM, never saved.
static EWRAM_DATA enum OrderKind sForcedOrderKind = ORDER_KIND_RANDOM;

static bool32 DrawOrder(enum OrderKind kind)
{
    u16 itemId = ITEM_NONE, count = 0, order = 0, p1, p2;
    bool32 tryDiscovery;

    GardenToday_Mark(GARDEN_TODAY_ORDER_ROLLED);
    if (kind == ORDER_KIND_RANDOM)
        tryDiscovery = VarGet(VAR_BERRY_GARDEN_LEVEL) >= GARDEN_LEVEL_PROPER && Random() % DISCOVERY_ONE_IN == 0;
    else
        tryDiscovery = (kind == ORDER_KIND_DISCOVERY);

    if (tryDiscovery)
    {
        itemId = NextDiscovery(&p1, &p2);
        if (itemId != ITEM_NONE)
        {
            count = 1;
            order = ORDER_DISCOVERY;
        }
    }
    if (itemId == ITEM_NONE && VarGet(VAR_BERRY_GARDEN_LEVEL) >= GARDEN_LEVEL_BACKYARD)
    {
        itemId = BerryLedger_RandomRegistered();
        if (itemId != ITEM_NONE)
            count = sOrderCountByGeneration[GetBerryGeneration(itemId)];
    }
    if (itemId == ITEM_NONE)
    {
        VarSet(VAR_BERRY_ORDER, 0);
        return FALSE;
    }
    order |= (itemId - LEDGER_FIRST_ITEM + 1) | (count << ORDER_COUNT_SHIFT) | (PickClient() << ORDER_CLIENT_SHIFT);
    VarSet(VAR_BERRY_ORDER, order);
    return TRUE;
}

// Draws today's order if it was not drawn yet. Returns TRUE if it drew one
// now (Bram announces it in this conversation).
u16 GardenOrder_Roll(void)
{
    enum OrderKind kind = sForcedOrderKind;

    if (GardenToday_Has(GARDEN_TODAY_ORDER_ROLLED))
        return FALSE;
    sForcedOrderKind = ORDER_KIND_RANDOM;
    return DrawOrder(kind);
}

// Returns GARDEN_ORDER_*; VAR_0x8004 = Berry, VAR_0x8005 = how many,
// VAR_0x8006 = client, VAR_0x8007 = TRUE for a discovery order.
u16 GardenOrder_Get(void)
{
    u16 order = VarGet(VAR_BERRY_ORDER);

    if (!GardenToday_Has(GARDEN_TODAY_ORDER_ROLLED) || (order & ORDER_BERRY_MASK) == 0)
        return GARDEN_ORDER_NONE;
    gSpecialVar_0x8004 = LEDGER_FIRST_ITEM + (order & ORDER_BERRY_MASK) - 1;
    gSpecialVar_0x8005 = (order & ORDER_COUNT_MASK) >> ORDER_COUNT_SHIFT;
    gSpecialVar_0x8006 = order >> ORDER_CLIENT_SHIFT;
    gSpecialVar_0x8007 = (order & ORDER_DISCOVERY) != 0;
    if (GardenToday_Has(GARDEN_TODAY_ORDER_DONE))
        return GARDEN_ORDER_DONE;
    return GARDEN_ORDER_OPEN;
}

// The Mulch that goes with today's pay: Surprise for a discovery, else
// Growth or Damp, a day each.
u16 GardenOrder_RewardMulch(void)
{
    if (VarGet(VAR_BERRY_ORDER) & ORDER_DISCOVERY)
        return ITEM_SURPRISE_MULCH;
    return (VarGet(VAR_DAYS) % 2) ? ITEM_DAMP_MULCH : ITEM_GROWTH_MULCH;
}

// After the script took the Berries: pays, marks the order done and returns
// the money paid (for the text). 0, and nothing paid, if there is no open order.
u16 GardenOrder_Pay(void)
{
    u32 pay;

    if (GardenOrder_Get() != GARDEN_ORDER_OPEN)
        return 0;
    pay = gSpecialVar_0x8005 * sOrderPayByGeneration[GetBerryGeneration(gSpecialVar_0x8004)];
    if (gSpecialVar_0x8007)
        pay *= 2;
    AddMoney(&gSaveBlock1Ptr->money, pay);
    GardenToday_Mark(GARDEN_TODAY_ORDER_DONE);
    return pay;
}

// Debug: forget today's order and force the kind of the next draw
// (VAR_0x8004 = TRUE for a discovery). The next talk with Bram draws and
// announces it exactly like the first conversation of a day.
void BerryDebug_NewOrder(void)
{
    VarSet(VAR_GARDEN_TODAY, VarGet(VAR_GARDEN_TODAY)
           & ~((1 << GARDEN_TODAY_ORDER_ROLLED) | (1 << GARDEN_TODAY_ORDER_DONE)));
    VarSet(VAR_BERRY_ORDER, 0);
    sForcedOrderKind = gSpecialVar_0x8004 ? ORDER_KIND_DISCOVERY : ORDER_KIND_COMMON;
}


// ---------------------------------------------------------------------------
// Who is where (part 8, section 2.1 / 14.3)
//
//            morning        day                         night
//   Bram     garden         house (seeds)               house, asleep
//   Laurel   house          garden; house on weekends   house (notebook)
//   Tilly    house (Sat/Sun)  garden stall (Sat/Sun)    away
//   Bugsy    away           garden, Tue/Thu, state >= 3 away
// Before the tutorial Bram stays in the house at any hour: the first visit is
// the classic one, and nobody misses the first Berry because of the clock.
// Nothing is saved: both maps ask again on every load (FLAG_TEMP_HIDE_*), so
// someone only changes place when the player comes back in, never in sight.
// ---------------------------------------------------------------------------

static void GardenCast_ApplyStory(u32 here, u32 period);

u32 GardenCast_PeriodOf(enum TimeOfDay timeOfDay)
{
    switch (timeOfDay)
    {
    case TIME_MORNING:
        return GARDEN_PERIOD_MORNING;
    case TIME_DAY:
        return GARDEN_PERIOD_DAY;
    default:
        return GARDEN_PERIOD_NIGHT;
    }
}

static bool32 IsWeekend(u32 weekday)
{
    return weekday == WEEKDAY_SAT || weekday == WEEKDAY_SUN;
}

u32 GardenCast_PlaceOf(u32 who, u32 period, u32 weekday, bool32 tutorialDone, u32 harvestKing)
{
    switch (who)
    {
    case GARDEN_CAST_BRAM:
        if (tutorialDone && period == GARDEN_PERIOD_MORNING)
            return GARDEN_PLACE_GARDEN;
        return GARDEN_PLACE_HOUSE;
    case GARDEN_CAST_LAUREL:
        if (period == GARDEN_PERIOD_DAY && !IsWeekend(weekday))
            return GARDEN_PLACE_GARDEN;
        return GARDEN_PLACE_HOUSE;
    case GARDEN_CAST_TILLY:
        if (!IsWeekend(weekday) || period == GARDEN_PERIOD_NIGHT)
            return GARDEN_PLACE_AWAY;
        return period == GARDEN_PERIOD_DAY ? GARDEN_PLACE_GARDEN : GARDEN_PLACE_HOUSE;
    case GARDEN_CAST_BUGSY:
        if (period == GARDEN_PERIOD_DAY && harvestKing >= HARVEST_KING_BUGSY_CAME
         && (weekday == WEEKDAY_TUE || weekday == WEEKDAY_THU))
            return GARDEN_PLACE_GARDEN;
        return GARDEN_PLACE_AWAY;
    }
    return GARDEN_PLACE_AWAY;
}

static const u16 sCastHideFlags[] =
{
    [GARDEN_CAST_BRAM]   = FLAG_TEMP_HIDE_BRAM,
    [GARDEN_CAST_LAUREL] = FLAG_TEMP_HIDE_LAUREL,
    [GARDEN_CAST_TILLY]  = FLAG_TEMP_HIDE_TILLY,
    [GARDEN_CAST_BUGSY]  = FLAG_TEMP_HIDE_BUGSY,
};

// ON_TRANSITION of Route30 and Route30_House, before anything spawns: freezes
// the period in VAR_TEMP_GARDEN_PERIOD (what they say matches where they
// stand) and hides whoever is not on this map now. FLAG_TEMP_* start clear on
// every load, so this only ever sets.
void GardenCast_Apply(void)
{
    u32 who, period, weekday, here;

    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_ROUTE30)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_ROUTE30))
        here = GARDEN_PLACE_GARDEN;
    else
        here = GARDEN_PLACE_HOUSE;
    period = GardenCast_PeriodOf(GetTimeOfDay());
    weekday = GetDayOfWeek();
    VarSet(VAR_TEMP_GARDEN_PERIOD, period);
    for (who = 0; who < ARRAY_COUNT(sCastHideFlags); who++)
    {
        if (GardenCast_PlaceOf(who, period, weekday, FlagGet(FLAG_GOT_BERRY_ROUTE_30_HOUSE),
                               VarGet(VAR_HARVEST_KING)) != here)
            FlagSet(sCastHideFlags[who]);
    }
    GardenCast_ApplyStory(here, period);
}

// For the scripts' weekday lines: TRUE on Saturday and Sunday.
u16 GardenCast_IsWeekend(void)
{
    return IsWeekend(GetDayOfWeek());
}

// ---------------------------------------------------------------------------
// Hearts and line banks (part 9, section 14.3)
//
// Every repeated event has a bank of 10 lines; the line is VAR_DAYS % N, so it
// is the same all day (a Harvest Moon villager) and none repeats within N days.
// Bram, Laurel, Tilly and Peony have hearts: one more for each day the player
// talks to them, up to 15. Lines 1-4 always, 5-7 from 5 days, 8-10 from 12.
// ---------------------------------------------------------------------------

#define HEARTS_BITS  4
#define HEARTS_MASK  0xF

u32 GardenHearts_Get(u32 who)
{
    if (who >= GARDEN_HEARTS_NONE)
        return 0;
    return (VarGet(VAR_GARDEN_HEARTS) >> (who * HEARTS_BITS)) & HEARTS_MASK;
}

static void GardenHearts_Set(u32 who, u32 hearts)
{
    u16 all = VarGet(VAR_GARDEN_HEARTS) & ~(HEARTS_MASK << (who * HEARTS_BITS));

    VarSet(VAR_GARDEN_HEARTS, all | (min(hearts, GARDEN_HEARTS_MAX) << (who * HEARTS_BITS)));
}

// How many lines of a bank are open: 10 without hearts, else 4, 7 or 10.
u32 GardenLine_Count(u32 who)
{
    u32 hearts;

    if (who >= GARDEN_HEARTS_NONE)
        return 10;
    hearts = GardenHearts_Get(who);
    if (hearts >= GARDEN_HEARTS_TIER2_DAYS)
        return 10;
    if (hearts >= GARDEN_HEARTS_TIER1_DAYS)
        return 7;
    return 4;
}

// VAR_0x8004 = GARDEN_HEARTS_*. The first talk of the day counts a heart
// (GARDEN_TODAY_TALKED_*); returns TRUE then, so the script knows it may say
// a reaction (section 14.3: reactions only on the first talk of the day).
u16 GardenHearts_Talk(void)
{
    u32 who = gSpecialVar_0x8004;

    if (who >= GARDEN_HEARTS_NONE || GardenToday_Has(GARDEN_TODAY_TALKED_BRAM + who))
        return FALSE;
    GardenToday_Mark(GARDEN_TODAY_TALKED_BRAM + who);
    GardenHearts_Set(who, GardenHearts_Get(who) + 1);
    return TRUE;
}

// VAR_0x8004 = GARDEN_HEARTS_* -> the line of the day, 0..N-1.
u16 GardenLine_Pick(void)
{
    return VarGet(VAR_DAYS) % GardenLine_Count(gSpecialVar_0x8004);
}

// ---------------------------------------------------------------------------
// Bram's news (part 9, section 9.8): things he says on the next talk, then
// forgets. The first garden harvest once in the whole game; a Berry new to
// the Book every time one grows in the garden.
// ---------------------------------------------------------------------------

#define NEWS_NEW_BERRY_MASK      0x007F
#define NEWS_FIRST_HARVEST       0x0080
#define NEWS_FIRST_HARVEST_TOLD  0x0100

void BerryLedger_RegisterHarvest(u32 treeId, u16 itemId)
{
    bool32 isNew = IsInLedger(itemId) && !BerryLedger_Has(itemId);
    u16 news;

    BerryLedger_RegisterItem(itemId);
    if (treeId < BERRY_TREE_GARDEN_FIRST || treeId > BERRY_TREE_GARDEN_LAST)
        return;
    news = VarGet(VAR_GARDEN_NEWS);
    if (!(news & NEWS_FIRST_HARVEST_TOLD))
        news |= NEWS_FIRST_HARVEST;
    if (isNew && !IsStarterBerry(itemId))
        news = (news & ~NEWS_NEW_BERRY_MASK) | (itemId - LEDGER_FIRST_ITEM + 1);
    VarSet(VAR_GARDEN_NEWS, news);
}

// One piece of news at a time, the first harvest first. Returns GARDEN_NEWS_*;
// for a new Berry, VAR_0x8004 = the Berry.
u16 GardenNews_Take(void)
{
    u16 news = VarGet(VAR_GARDEN_NEWS);

    if (news & NEWS_FIRST_HARVEST)
    {
        VarSet(VAR_GARDEN_NEWS, (news & ~NEWS_FIRST_HARVEST) | NEWS_FIRST_HARVEST_TOLD);
        return GARDEN_NEWS_FIRST_HARVEST;
    }
    if (news & NEWS_NEW_BERRY_MASK)
    {
        gSpecialVar_0x8004 = LEDGER_FIRST_ITEM + (news & NEWS_NEW_BERRY_MASK) - 1;
        VarSet(VAR_GARDEN_NEWS, news & ~NEWS_NEW_BERRY_MASK);
        return GARDEN_NEWS_NEW_BERRY;
    }
    return GARDEN_NEWS_NONE;
}

// VAR_0x8004 = TYPE_* -> TRUE if the Pokemon walking behind the player (the
// first live one) has that type; VAR_0x8005 = its species.
u16 GardenLead_IsType(void)
{
    struct Pokemon *mon = GetFirstLiveMon();
    u32 species;

    if (mon == NULL)
        return FALSE;
    species = GetMonData(mon, MON_DATA_SPECIES);
    gSpecialVar_0x8005 = species;
    return gSpeciesInfo[species].types[0] == gSpecialVar_0x8004
        || gSpeciesInfo[species].types[1] == gSpecialVar_0x8004;
}

// How many of the ten garden plots have something growing.
u16 GardenPlots_Planted(void)
{
    u32 id, planted = 0;

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        if (GetBerryTreeInfo(id)->stage != BERRY_STAGE_NO_BERRY)
            planted++;
    }
    return planted;
}

// Debug: everyone's hearts to VAR_0x8004 (0, 5, 12 or 15).
void BerryDebug_SetHearts(void)
{
    u32 who;

    for (who = 0; who < GARDEN_HEARTS_NONE; who++)
        GardenHearts_Set(who, gSpecialVar_0x8004);
}

// ---------------------------------------------------------------------------
// Pests and weeds (part 10, section 7)
//
// Only in the ten garden plots (route trees never get either). Eight families
// live only here now - Wurmple, Blipbug, Volbeat, Illumise, Scatterbug,
// Combee, Rellor and Dwebble are out of src/data/wild_encounters.json.
// The pest: the mulch first (half the time: Gooey/Rich -> Rellor rolling it,
// Stable -> Dwebble moving into the stone), then the Berry's colour picks the
// row, the hour the common one, and the Berry's generation how often the
// uncommon and the rare come. Purple Berries share the blue row.
// ---------------------------------------------------------------------------

#define PEST_CHANCE              15   // % per two hours of growth
#define PEST_CHANCE_BUG_HOTEL    30
#define PEST_LEVEL_BASE          10
#define PEST_LEVEL_PER_BADGE     4
#define PEST_LEVEL_MAX           60

enum PestSlot
{
    PEST_COMMON_DAY,
    PEST_COMMON_NIGHT,
    PEST_UNCOMMON,
    PEST_RARE,
    PEST_SLOT_COUNT,
};

enum PestRow
{
    PEST_ROW_RED,
    PEST_ROW_BLUE,
    PEST_ROW_PINK,
    PEST_ROW_GREEN,
    PEST_ROW_YELLOW,
    PEST_ROW_COUNT,
};

static const u16 sPests[PEST_ROW_COUNT][PEST_SLOT_COUNT] =
{
    [PEST_ROW_RED]    = { SPECIES_LEDYBA,      SPECIES_SPINARAK,  SPECIES_WURMPLE,          SPECIES_HERACROSS },
    [PEST_ROW_BLUE]   = { SPECIES_BLIPBUG,     SPECIES_VOLBEAT,   SPECIES_SURSKIT,          SPECIES_JOLTIK },
    [PEST_ROW_PINK]   = { SPECIES_CUTIEFLY,    SPECIES_ILLUMISE,  SPECIES_SCATTERBUG_FANCY, SPECIES_SHUCKLE },
    [PEST_ROW_GREEN]  = { SPECIES_BURMY_PLANT, SPECIES_KRICKETOT, SPECIES_SCATTERBUG_FANCY, SPECIES_SEWADDLE },
    [PEST_ROW_YELLOW] = { SPECIES_COMBEE,      SPECIES_VENONAT,   SPECIES_KRICKETOT,        SPECIES_HERACROSS },
};

// The eight families that only come from here, by their first stage (Bugsy's
// "you found all of them").
static const u16 sGardenOnlyPests[] =
{
    SPECIES_WURMPLE, SPECIES_BLIPBUG, SPECIES_VOLBEAT, SPECIES_ILLUMISE,
    SPECIES_SCATTERBUG, SPECIES_COMBEE, SPECIES_RELLOR, SPECIES_DWEBBLE,
};

static const u8 sPestRowByColor[] =
{
    [BERRY_COLOR_RED]    = PEST_ROW_RED,
    [BERRY_COLOR_BLUE]   = PEST_ROW_BLUE,
    [BERRY_COLOR_PURPLE] = PEST_ROW_BLUE,
    [BERRY_COLOR_GREEN]  = PEST_ROW_GREEN,
    [BERRY_COLOR_YELLOW] = PEST_ROW_YELLOW,
    [BERRY_COLOR_PINK]   = PEST_ROW_PINK,
};

bool32 IsBerryGardenTree(u32 treeId)
{
    return treeId >= BERRY_TREE_GARDEN_FIRST && treeId <= BERRY_TREE_GARDEN_LAST;
}

// % chance per check (src/berry.c TryForPests): doubled by the Bug Hotel.
u32 GardenPest_Chance(void)
{
    if (VarGet(VAR_BERRY_GARDEN_LEVEL) >= GARDEN_LEVEL_BUG_HOTEL)
        return PEST_CHANCE_BUG_HOTEL;
    return PEST_CHANCE;
}

// The rule with every die already thrown: roll 0..99 for the slot, mulchRoll
// TRUE for the half of the time the mulch wins. Scatterbug comes back as
// SPECIES_SCATTERBUG_FANCY, which the caller turns into one of the patterns.
u16 GardenPest_Pick(u32 color, bool32 night, u32 generation, u16 mulchItem, u32 roll, bool32 mulchRoll)
{
    u32 row = color < ARRAY_COUNT(sPestRowByColor) ? sPestRowByColor[color] : PEST_ROW_GREEN;
    u32 common, uncommon;

    if (mulchRoll && (mulchItem == ITEM_GOOEY_MULCH || mulchItem == ITEM_RICH_MULCH))
        return SPECIES_RELLOR;
    if (mulchRoll && mulchItem == ITEM_STABLE_MULCH)
        return SPECIES_DWEBBLE;
    if (generation <= 1)
        common = 70, uncommon = 27;
    else if (generation <= 3)
        common = 50, uncommon = 38;
    else
        common = 30, uncommon = 40;
    if (roll < common)
        return sPests[row][night ? PEST_COMMON_NIGHT : PEST_COMMON_DAY];
    if (roll < common + uncommon)
        return sPests[row][PEST_UNCOMMON];
    return sPests[row][PEST_RARE];
}

// Act 1a needs it after the battle (GardenPest_LastSpecies, part 12).
static EWRAM_DATA u16 sLastPestSpecies = SPECIES_NONE;

// The pest that comes out of this garden tree now.
u16 GardenPest_Species(u32 treeId)
{
    struct BerryTree *tree = GetBerryTreeInfo(treeId);
    u16 itemId = BerryTypeToItemId(tree->berry);
    u16 mulchItem = tree->mulch ? ITEM_GROWTH_MULCH + tree->mulch - 1 : ITEM_NONE;
    bool32 night = GardenCast_PeriodOf(GetTimeOfDay()) == GARDEN_PERIOD_NIGHT;
    u16 species;

    species = GardenPest_Pick(GetBerryInfo(tree->berry)->color, night, GetBerryGeneration(itemId),
                              mulchItem, Random() % 100, Random() % 2);
    species = GetWildFormVariantSpecies(species);
    sLastPestSpecies = species;
    return species;
}

// 10 + 4 per badge (all 16), up to 60, then the wild level scaling the player
// chose, like any wild Pokemon.
u8 GardenPest_Level(u16 species)
{
    u32 badge, level = PEST_LEVEL_BASE;

    for (badge = FLAG_BADGE01_GET; badge <= FLAG_BADGE08_GET; badge++)
    {
        if (FlagGet(badge))
            level += PEST_LEVEL_PER_BADGE;
    }
    for (badge = FLAG_BADGE09_GET; badge <= FLAG_BADGE16_GET; badge++)
    {
        if (FlagGet(badge))
            level += PEST_LEVEL_PER_BADGE;
    }
    level = min(level, PEST_LEVEL_MAX);
    return CalculateWildScaledLevel(species, level, 0);
}

// The tree the player is facing is a garden plot (berry_tree.inc: the pest
// lines of bank P are only for the garden).
u16 GardenPest_IsGardenTree(void)
{
    return IsBerryGardenTree(GetObjectEventBerryTreeId(gSelectedObjectEvent));
}

// Laurel's reaction: 1 = a weed in bed A, 2 = in bed B, 0 = none.
u16 GardenWeeds_Bed(void)
{
    u32 id;

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        if (GetBerryTreeInfo(id)->weeds && GetBerryTreeInfo(id)->stage != BERRY_STAGE_NO_BERRY)
            return id <= BERRY_TREE_GARDEN_A6 ? 1 : 2;
    }
    return 0;
}

// Bugsy's reaction: every one of the eight garden-only families caught.
u16 GardenPests_AllCaught(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sGardenOnlyPests); i++)
    {
        if (!GetSetPokedexFlag(SpeciesToNationalPokedexNum(sGardenOnlyPests[i]), FLAG_GET_CAUGHT))
            return FALSE;
    }
    return TRUE;
}

// ---------------------------------------------------------------------------
// Klara's morning raid (part 11, sections 13.4 and 14.4 I)
//
// GardenRollDay draws the morning (1 in 7, level 2+). On a load of Route30 in
// that morning, with a ripe plot, she stands in front of one; talking to her
// is a battle with no blackout. She wins, or the player leaves Route30 without
// talking to her: that plot is emptied. VAR_GARDEN_RIVALS keeps her between
// loads (it is the only state that has to survive the player walking out):
//   bits 0-3  wins against her (the 5th brings the mochi line)
//   bit  4    she is in the garden now, waiting
//   bits 5-8  the plot she is after (0..9 from GARDEN_FIRST)
//   bits 9-11 Bram's line about her for his next talk (0 none, 1..5)
// ---------------------------------------------------------------------------

#define RIVALS_WINS_MASK      0x000F
#define RIVALS_WAITING        0x0010
#define RIVALS_PLOT_SHIFT     5
#define RIVALS_PLOT_MASK      0x01E0
#define RIVALS_BRAM_SHIFT     9
#define RIVALS_BRAM_MASK      0x0E00

// Where she stands for each plot (its free side; never Bram's (27,44)) and
// which way she looks. Measured on Route30 (data/maps/Route30/scripts.inc).
static const struct { s8 x, y; u8 movement; } sKlaraSpots[] =
{
    { 28, 42, MOVEMENT_TYPE_FACE_DOWN },  // A1 (28,43)
    { 29, 42, MOVEMENT_TYPE_FACE_DOWN },  // A2 (29,43)
    { 31, 43, MOVEMENT_TYPE_FACE_LEFT },  // A3 (30,43)
    { 28, 45, MOVEMENT_TYPE_FACE_UP },    // A4 (28,44)
    { 29, 45, MOVEMENT_TYPE_FACE_UP },    // A5 (29,44)
    { 30, 45, MOVEMENT_TYPE_FACE_UP },    // A6 (30,44)
    { 30, 40, MOVEMENT_TYPE_FACE_DOWN },  // B1 (30,41)
    { 31, 40, MOVEMENT_TYPE_FACE_DOWN },  // B2 (31,41)
    { 29, 42, MOVEMENT_TYPE_FACE_RIGHT }, // B3 (30,42)
    { 31, 43, MOVEMENT_TYPE_FACE_UP },    // B4 (31,42)
};
STATIC_ASSERT(ARRAY_COUNT(sKlaraSpots) == BERRY_TREE_GARDEN_LAST - BERRY_TREE_GARDEN_FIRST + 1, KlaraSpotEveryPlot);

// The tree is emptied the way a harvest empties it: marked "just picked", so
// it does not play the growth sparkle. With the sparkle, a plot emptied in
// sight corrupted the graphics of Bram and Klara (QA 03/10/2026, part 11: the
// sparkle sprite drew over their tiles); a harvest never shows it.
static void KlaraTakesThePlot(u16 rivals)
{
    u32 plot = (rivals & RIVALS_PLOT_MASK) >> RIVALS_PLOT_SHIFT;

    SetBerryTreeJustPicked(LOCALID_ROUTE30_GARDEN_A1 + plot, gSaveBlock1Ptr->location.mapNum,
                           gSaveBlock1Ptr->location.mapGroup);
    RemoveBerryTree(BERRY_TREE_GARDEN_FIRST + plot);
    GardenToday_Mark(GARDEN_TODAY_KLARA_RESOLVED);
}

// Route30 ON_TRANSITION, VAR_0x8004 = her local id. TRUE = she is here now
// (her template is moved in front of the plot); FALSE = hide her. If she was
// left waiting on the last visit, she took that plot and is gone.
u16 GardenKlara_Place(void)
{
    u16 rivals = VarGet(VAR_GARDEN_RIVALS);
    u32 id, ripe = 0, pick;

    if (rivals & RIVALS_WAITING)
    {
        KlaraTakesThePlot(rivals);
        rivals &= ~(RIVALS_WAITING | RIVALS_BRAM_MASK);
        rivals |= (1 + Random() % 4) << RIVALS_BRAM_SHIFT;   // one of his first four
        VarSet(VAR_GARDEN_RIVALS, rivals);
        return FALSE;
    }
    if (!GardenToday_Has(GARDEN_TODAY_KLARA_COMES) || GardenToday_Has(GARDEN_TODAY_KLARA_RESOLVED)
     || GardenCast_PeriodOf(GetTimeOfDay()) != GARDEN_PERIOD_MORNING)
        return FALSE;
    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        if (GetBerryTreeInfo(id)->stage == BERRY_STAGE_BERRIES)
            ripe++;
    }
    if (ripe == 0)
        return FALSE;
    pick = Random() % ripe;
    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        if (GetBerryTreeInfo(id)->stage == BERRY_STAGE_BERRIES && pick-- == 0)
            break;
    }
    id -= BERRY_TREE_GARDEN_FIRST;
    SetObjEventTemplateCoords(gSpecialVar_0x8004, sKlaraSpots[id].x, sKlaraSpots[id].y);
    SetObjEventTemplateMovementType(gSpecialVar_0x8004, sKlaraSpots[id].movement);
    rivals &= ~RIVALS_PLOT_MASK;
    VarSet(VAR_GARDEN_RIVALS, rivals | RIVALS_WAITING | (id << RIVALS_PLOT_SHIFT));
    return TRUE;
}

// After the battle. VAR_0x8004 = TRUE if the player won, VAR_0x8005 = the
// line she said (0..4; Bram answers it). Returns the wins so far (the 5th
// brings the mochi line). A loss empties her plot.
u16 GardenKlara_Resolve(void)
{
    u16 rivals = VarGet(VAR_GARDEN_RIVALS);
    u32 wins = rivals & RIVALS_WINS_MASK, bramLine;

    if (gSpecialVar_0x8004)
    {
        if (wins < RIVALS_WINS_MASK)
            wins++;
        bramLine = 5;
        GardenToday_Mark(GARDEN_TODAY_KLARA_RESOLVED);
    }
    else
    {
        KlaraTakesThePlot(rivals);
        bramLine = 1 + gSpecialVar_0x8005 % 4;
    }
    rivals &= ~(RIVALS_WINS_MASK | RIVALS_WAITING | RIVALS_BRAM_MASK);
    VarSet(VAR_GARDEN_RIVALS, rivals | wins | (bramLine << RIVALS_BRAM_SHIFT));
    return wins;
}

// Bram's next talk: 0, or his line 1..5 about her (then forgotten).
u16 GardenKlara_TakeBramLine(void)
{
    u16 rivals = VarGet(VAR_GARDEN_RIVALS);
    u32 line = (rivals & RIVALS_BRAM_MASK) >> RIVALS_BRAM_SHIFT;

    VarSet(VAR_GARDEN_RIVALS, rivals & ~RIVALS_BRAM_MASK);
    return line;
}

// Debug: Klara comes this morning (and is not resolved yet).
void BerryDebug_KlaraComes(void)
{
    GardenToday_Mark(GARDEN_TODAY_KLARA_COMES);
    VarSet(VAR_GARDEN_TODAY, VarGet(VAR_GARDEN_TODAY) & ~(1 << GARDEN_TODAY_KLARA_RESOLVED));
    VarSet(VAR_GARDEN_RIVALS, VarGet(VAR_GARDEN_RIVALS) & ~RIVALS_WAITING);
}

// Tilly's prize: one of the four Mulches she sells, at random.
u16 GardenTilly_PrizeMulch(void)
{
    static const u16 sMulches[] = { ITEM_GROWTH_MULCH, ITEM_DAMP_MULCH, ITEM_STABLE_MULCH, ITEM_GOOEY_MULCH };

    return sMulches[Random() % ARRAY_COUNT(sMulches)];
}

// ---------------------------------------------------------------------------
// The story, prologue to Act 4 (part 12, sections 8.2-8.9). The scripts run
// the scenes; this holds the conditions and who stands where for them.
// ---------------------------------------------------------------------------

#define STORY_SHIFT  9   // VAR_GARDEN_NEWS bits 9..15 (GARDEN_STORY_*)

// VAR_0x8004 = GARDEN_STORY_*: TRUE if that one-time line was already said.
u16 GardenStory_Check(void)
{
    return (VarGet(VAR_GARDEN_NEWS) >> (STORY_SHIFT + gSpecialVar_0x8004)) & 1;
}

void GardenStory_Mark(void)
{
    VarSet(VAR_GARDEN_NEWS, VarGet(VAR_GARDEN_NEWS) | (1 << (STORY_SHIFT + gSpecialVar_0x8004)));
}

// The Enigma's stage in Laurel's plot (BERRY_STAGE_*), 0 if anything else grows there.
u16 GardenKingsPlot_Stage(void)
{
    struct BerryTree *tree = GetBerryTreeInfo(BERRY_TREE_KINGS_PLOT);

    if (tree->stage == BERRY_STAGE_NO_BERRY || BerryTypeToItemId(tree->berry) != ITEM_ENIGMA_BERRY)
        return BERRY_STAGE_NO_BERRY;
    return tree->stage;
}

// TRUE if an Enigma grows in one of the ten beds (Act 3: "That's a bed.").
u16 GardenPlots_HaveEnigma(void)
{
    u32 id;

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_GARDEN_LAST; id++)
    {
        struct BerryTree *tree = GetBerryTreeInfo(id);

        if (tree->stage != BERRY_STAGE_NO_BERRY && BerryTypeToItemId(tree->berry) == ITEM_ENIGMA_BERRY)
            return TRUE;
    }
    return FALSE;
}

// Act 1c: the garden-only families with any member caught (section 7.1).
static const u16 sGardenOnlyFamilies[][5] =
{
    { SPECIES_WURMPLE, SPECIES_SILCOON, SPECIES_BEAUTIFLY, SPECIES_CASCOON, SPECIES_DUSTOX },
    { SPECIES_BLIPBUG, SPECIES_DOTTLER, SPECIES_ORBEETLE },
    { SPECIES_VOLBEAT },
    { SPECIES_ILLUMISE },
    { SPECIES_SCATTERBUG, SPECIES_SPEWPA, SPECIES_VIVILLON },
    { SPECIES_COMBEE, SPECIES_VESPIQUEN },
    { SPECIES_RELLOR, SPECIES_RABSCA },
    { SPECIES_DWEBBLE, SPECIES_CRUSTLE },
};

u16 GardenPests_FamiliesCaught(void)
{
    u32 family, member, caught = 0;

    for (family = 0; family < ARRAY_COUNT(sGardenOnlyFamilies); family++)
    {
        for (member = 0; member < ARRAY_COUNT(sGardenOnlyFamilies[0]) && sGardenOnlyFamilies[family][member]; member++)
        {
            if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(sGardenOnlyFamilies[family][member]), FLAG_GET_CAUGHT))
            {
                caught++;
                break;
            }
        }
    }
    return caught;
}

// The species of the last garden pest (Act 1a: Laurel names it).
u16 GardenPest_LastSpecies(void)
{
    return sLastPestSpecies;
}

static void GardenCast_ApplyStory(u32 here, u32 period)
{
    u32 state = VarGet(VAR_HARVEST_KING);
    bool32 laurelKneels = state == HARVEST_KING_NOTEBOOK && period == GARDEN_PERIOD_DAY
                       && GardenKingsPlot_Stage() >= BERRY_STAGE_SPROUTED;

    if (here == GARDEN_PLACE_HOUSE)
    {
        // Act 4: she is out at her plot all day.
        if (laurelKneels)
            FlagSet(FLAG_TEMP_HIDE_LAUREL);
        return;
    }
    // Act 1b: Bugsy's first visit, any day, once the player has the 2nd badge.
    if (state == HARVEST_KING_VISITORS && FlagGet(FLAG_BADGE02_GET) && period == GARDEN_PERIOD_DAY)
        FlagClear(FLAG_TEMP_HIDE_BUGSY);
    // Act 2: the night visitor, eating from bed B.
    if (!(state == HARVEST_KING_ACT1_DONE && period == GARDEN_PERIOD_NIGHT
       && VarGet(VAR_BERRY_GARDEN_LEVEL) >= GARDEN_LEVEL_CHANNEL))
        FlagSet(FLAG_TEMP_HIDE_SPECTRIER);
    // Act 4: Laurel on her knees by her plot (23,38), from its south side.
    if (laurelKneels)
    {
        FlagClear(FLAG_TEMP_HIDE_LAUREL);
        SetObjEventTemplateCoords(LOCALID_ROUTE30_LAUREL, 23, 39);
        SetObjEventTemplateMovementType(LOCALID_ROUTE30_LAUREL, MOVEMENT_TYPE_FACE_UP);
    }
}

// Debug: the story state (VAR_0x8004) and the one-time lines that come before it.
void BerryDebug_SetStory(void)
{
    u16 news = VarGet(VAR_GARDEN_NEWS) & ~(((1 << GARDEN_STORY_COUNT) - 1) << STORY_SHIFT);

    if (gSpecialVar_0x8004 > HARVEST_KING_VISITORS)
        news |= 1 << (STORY_SHIFT + GARDEN_STORY_BRAM_BUGS);
    if (gSpecialVar_0x8004 > HARVEST_KING_FOOTPRINTS)
        news |= 1 << (STORY_SHIFT + GARDEN_STORY_LAUREL_HEARD);
    VarSet(VAR_GARDEN_NEWS, news);
    VarSet(VAR_HARVEST_KING, gSpecialVar_0x8004);
}

// Debug: an Enigma just sprouted in Laurel's plot (Act 4).
void BerryDebug_KingsPlotSprout(void)
{
    struct BerryTree *tree = GetBerryTreeInfo(BERRY_TREE_KINGS_PLOT);

    *tree = (struct BerryTree){0};
    tree->berry = ItemIdToBerryType(ITEM_ENIGMA_BERRY);
    tree->stage = BERRY_STAGE_SPROUTED;
    tree->minutesUntilNextStage = 60;
}
