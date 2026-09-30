// Berry Master's garden on Route 30.
//
// Design:  .claude/berry_master/REI_DA_COLHEITA.md
// Plan:    .claude/berry_master/PLANO_DE_IMPLEMENTACAO.md
//
// This file holds the RULES; the flow (who says what, when) is the map script
// of Route30 and Route30_House, which only asks questions through the specials
// below.

#include "global.h"
#include "berry_garden.h"
#include "event_data.h"
#include "random.h"
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

void GardenRollDay(void)
{
    if (FlagGet(FLAG_DAILY_GARDEN_NEW_DAY))
        return;

    VarSet(VAR_GARDEN_TODAY, 0);
    FlagSet(FLAG_DAILY_GARDEN_NEW_DAY);

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
