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
// (part 16) and is deliberately not in this list.
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
