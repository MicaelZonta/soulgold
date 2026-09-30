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
#include "event_data.h"
#include "item.h"
#include "list_menu.h"
#include "malloc.h"
#include "money.h"
#include "random.h"
#include "script_menu.h"
#include "string_util.h"
#include "constants/berry.h"
#include "constants/flags.h"
#include "constants/items.h"
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

void GardenRollDay(void)
{
    if (FlagGet(FLAG_DAILY_GARDEN_NEW_DAY))
        return;

    VarSet(VAR_GARDEN_TODAY, 0);
    FlagSet(FLAG_DAILY_GARDEN_NEW_DAY);
    FinishGardenWork();

    // The day's draws go here, once each, when their part exists:
    //   Klara's raid, 1 morning in 7, garden level 2+ (part 11) -> GARDEN_TODAY_KLARA_COMES
    //   Mustard, 1 Sunday in 4, story state 15 (part 16)          -> GARDEN_TODAY_MUSTARD_COMES
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
