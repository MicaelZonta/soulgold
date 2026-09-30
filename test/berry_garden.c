#include "global.h"
#include "berry.h"
#include "berry_garden.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "item.h"
#include "test/test.h"
#include "constants/berry.h"
#include "constants/event_object_movement.h"
#include "constants/flags.h"
#include "constants/items.h"

// Berry Master's garden (.claude/berry_master/PLANO_DE_IMPLEMENTACAO.md,
// parts 2 and 3).

static void ClearLedger(void)
{
    u32 flag;

    for (flag = FLAG_BERRY_LEDGER_START; flag <= FLAG_BERRY_LEDGER_END; flag++)
        FlagClear(flag);
    VarSet(VAR_BERRY_LEDGER_MILESTONE, 0);
}

static void RegisterFirst(u32 howMany)
{
    u32 i;

    for (i = 0; i < howMany; i++)
        BerryLedger_RegisterItem(FIRST_BERRY_INDEX + i);
}

TEST("Garden plots are ten contiguous tree slots with Laurel's plot right after")
{
    EXPECT_EQ(BERRY_TREE_GARDEN_LAST - BERRY_TREE_GARDEN_FIRST + 1, 10);
    EXPECT_EQ(BERRY_TREE_KINGS_PLOT, BERRY_TREE_GARDEN_LAST + 1);
    EXPECT_LT(BERRY_TREE_KINGS_PLOT, BERRY_TREES_COUNT);
}

TEST("Garden plots and Laurel's plot never grow a natural Berry back")
{
    u32 id;

    ClearBerryTrees();
    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_KINGS_PLOT; id++)
        RemoveBerryTree(id);
    BerryTreeTimeUpdate(NATURAL_BERRY_TREE_REGEN_MINUTES * 10);

    for (id = BERRY_TREE_GARDEN_FIRST; id <= BERRY_TREE_KINGS_PLOT; id++)
    {
        struct BerryTree *tree = GetBerryTreeInfo(id);
        EXPECT_EQ((u32)tree->stage, BERRY_STAGE_NO_BERRY);
        EXPECT_EQ((u32)tree->berry, BERRY_NONE);
    }
}

TEST("The route Oran tree slot still grows its Oran back (WorldHub uses it)")
{
    struct BerryTree *tree;

    ClearBerryTrees();
    RemoveBerryTree(BERRY_TREE_ORAN_2);
    BerryTreeTimeUpdate(NATURAL_BERRY_TREE_REGEN_MINUTES);
    tree = GetBerryTreeInfo(BERRY_TREE_ORAN_2);

    EXPECT_EQ((u32)tree->stage, BERRY_STAGE_BERRIES);
    EXPECT_EQ((u32)tree->berry, ITEM_TO_BERRY(ITEM_ORAN_BERRY));
}

TEST("Book of Berries registers Berries and nothing else")
{
    ClearLedger();

    BerryLedger_RegisterItem(ITEM_SITRUS_BERRY);
    BerryLedger_RegisterItem(ITEM_POTION);
    BerryLedger_RegisterItem(ITEM_ENIGMA_BERRY_E_READER);
    BerryLedger_RegisterItem(ITEM_SITRUS_BERRY);

    EXPECT(BerryLedger_Has(ITEM_SITRUS_BERRY));
    EXPECT(!BerryLedger_Has(ITEM_ORAN_BERRY));
    EXPECT(!BerryLedger_Has(ITEM_POTION));
    EXPECT_EQ(BerryLedger_Count(), 1);
}

TEST("Book of Berries spans Cheri to Maranga")
{
    ClearLedger();

    BerryLedger_RegisterItem(ITEM_CHERI_BERRY);
    BerryLedger_RegisterItem(ITEM_MARANGA_BERRY);

    EXPECT(FlagGet(FLAG_BERRY_LEDGER_START));
    EXPECT(FlagGet(FLAG_BERRY_LEDGER_END));
    EXPECT_EQ(BerryLedger_Count(), 2);

    RegisterFirst(ITEM_MARANGA_BERRY - FIRST_BERRY_INDEX + 1);
    EXPECT_EQ(BerryLedger_Count(), 67);
}

TEST("Bram's eight starting Berries can be registered any number of times")
{
    ClearLedger();

    BerryLedger_RegisterStarters();
    BerryLedger_RegisterStarters();

    EXPECT_EQ(BerryLedger_Count(), 8);
    EXPECT(BerryLedger_Has(ITEM_CHERI_BERRY));
    EXPECT(BerryLedger_Has(ITEM_PERSIM_BERRY));
    EXPECT(!BerryLedger_Has(ITEM_SITRUS_BERRY));
}

TEST("Bram's daily draw only gives registered Berries, never Lansat, Starf or Enigma")
{
    u32 i;

    ClearLedger();
    EXPECT_EQ(BerryLedger_RandomRegistered(), ITEM_NONE);

    BerryLedger_RegisterItem(ITEM_LANSAT_BERRY);
    BerryLedger_RegisterItem(ITEM_STARF_BERRY);
    BerryLedger_RegisterItem(ITEM_ENIGMA_BERRY);
    EXPECT_EQ(BerryLedger_RandomRegistered(), ITEM_NONE);

    BerryLedger_RegisterItem(ITEM_ORAN_BERRY);
    for (i = 0; i < 50; i++)
        EXPECT_EQ(BerryLedger_RandomRegistered(), ITEM_ORAN_BERRY);
}

TEST("Bram's daily draw reaches every registered Berry")
{
    u32 i, sawCheri = 0, sawMaranga = 0;

    ClearLedger();
    BerryLedger_RegisterItem(ITEM_CHERI_BERRY);
    BerryLedger_RegisterItem(ITEM_MARANGA_BERRY);

    for (i = 0; i < 200; i++)
    {
        u16 item = BerryLedger_RandomRegistered();
        EXPECT(item == ITEM_CHERI_BERRY || item == ITEM_MARANGA_BERRY);
        if (item == ITEM_CHERI_BERRY)
            sawCheri++;
        else
            sawMaranga++;
    }
    EXPECT_GT(sawCheri, 0);
    EXPECT_GT(sawMaranga, 0);
}

TEST("Laurel's rare draw only gives registered rares, never the Enigma")
{
    u32 i;

    ClearLedger();
    BerryLedger_RegisterStarters();
    BerryLedger_RegisterItem(ITEM_ENIGMA_BERRY);
    EXPECT_EQ(BerryLedger_RandomRegisteredRare(), ITEM_NONE);

    BerryLedger_RegisterItem(ITEM_LIECHI_BERRY);
    for (i = 0; i < 50; i++)
        EXPECT_EQ(BerryLedger_RandomRegisteredRare(), ITEM_LIECHI_BERRY);
}

TEST("Book milestones are paid once each, lowest unpaid first")
{
    ClearLedger();

    RegisterFirst(11);
    EXPECT_EQ(BerryLedger_PendingMilestone(), 0);

    RegisterFirst(12);
    EXPECT_EQ(BerryLedger_PendingMilestone(), 12);
    VarSet(VAR_BERRY_LEDGER_MILESTONE, 12);
    EXPECT_EQ(BerryLedger_PendingMilestone(), 0);

    // An old save with a big Book: 20 and 30 are both owed, 20 comes first.
    RegisterFirst(30);
    EXPECT_EQ(BerryLedger_PendingMilestone(), 20);
    VarSet(VAR_BERRY_LEDGER_MILESTONE, 20);
    EXPECT_EQ(BerryLedger_PendingMilestone(), 30);

    // 66 is the epilogue's title, not one of Bram's prizes.
    RegisterFirst(67);
    VarSet(VAR_BERRY_LEDGER_MILESTONE, 60);
    EXPECT_EQ(BerryLedger_PendingMilestone(), 0);
}

TEST("Harvesting a garden plot puts the Berry in the bag and in the Book")
{
    struct BerryTree *tree;

    ClearLedger();
    ClearBag();
    ClearBerryTrees();
    PlantBerryTree(BERRY_TREE_GARDEN_A1, ITEM_TO_BERRY(ITEM_SITRUS_BERRY), BERRY_STAGE_BERRIES, TRUE);
    tree = GetBerryTreeInfo(BERRY_TREE_GARDEN_A1);
    tree->berryYield = 3;
    gObjectEvents[0].trainerRange_berryTreeId = BERRY_TREE_GARDEN_A1;
    gSelectedObjectEvent = 0;

    ObjectEventInteractionPickBerryTree();

    EXPECT(gSpecialVar_0x8004);
    EXPECT(CheckBagHasItem(ITEM_SITRUS_BERRY, 3));
    EXPECT(BerryLedger_Has(ITEM_SITRUS_BERRY));
}

// ObjectEventInteractionPickBerryTree's result, named only in
// data/scripts/berry_tree.inc (.set BERRY_MUTATION_SPACE_IN_BAG, 3).
#define PICKED_WITH_MUTATION 3

// Mutations (part 4). Two garden plots side by side as live objects: the
// neighbour already planted, then the plot planted again and again until the
// 25% roll hits (or 200 tries, which a working recipe never needs).
static void PlaceTreeObject(u32 slot, u32 treeId, s16 x, s16 y)
{
    memset(&gObjectEvents[slot], 0, sizeof(gObjectEvents[slot]));
    gObjectEvents[slot].active = TRUE;
    gObjectEvents[slot].movementType = MOVEMENT_TYPE_BERRY_TREE_GROWTH;
    gObjectEvents[slot].trainerRange_berryTreeId = treeId;
    gObjectEvents[slot].currentCoords.x = x;
    gObjectEvents[slot].currentCoords.y = y;
}

static u16 HarvestMutationAfterPlanting(u16 planted, u16 neighbour, u16 thirdNeighbour)
{
    u32 tries;

    ClearBag();
    ClearBerryTrees();
    PlaceTreeObject(0, BERRY_TREE_GARDEN_A1, 10, 10);
    PlaceTreeObject(1, BERRY_TREE_GARDEN_A2, 11, 10);
    PlaceTreeObject(2, BERRY_TREE_GARDEN_A4, 10, 11);
    PlantBerryTree(BERRY_TREE_GARDEN_A2, ITEM_TO_BERRY(neighbour), BERRY_STAGE_BERRIES, TRUE);
    if (thirdNeighbour != ITEM_NONE)
        PlantBerryTree(BERRY_TREE_GARDEN_A4, ITEM_TO_BERRY(thirdNeighbour), BERRY_STAGE_BERRIES, TRUE);

    for (tries = 0; tries < 200; tries++)
    {
        PlantBerryTree(BERRY_TREE_GARDEN_A1, ITEM_TO_BERRY(planted), BERRY_STAGE_BERRIES, TRUE);
        GetBerryTreeInfo(BERRY_TREE_GARDEN_A1)->berryYield = 1;
        gSelectedObjectEvent = 0;
        ObjectEventInteractionPickBerryTree();
        if (gSpecialVar_0x8004 == PICKED_WITH_MUTATION)
        {
            u32 item;
            for (item = FIRST_BERRY_INDEX; item <= ITEM_MARANGA_BERRY; item++)
            {
                if (item != planted && CheckBagHasItem(item, 1))
                    return item;
            }
        }
        RemoveBerryTree(BERRY_TREE_GARDEN_A1);
    }
    return ITEM_NONE;
}

TEST("Cheri planted next to Chesto crosses into a Lum, and the Lum goes in the Book")
{
    ClearLedger();
    EXPECT_EQ(HarvestMutationAfterPlanting(ITEM_CHERI_BERRY, ITEM_CHESTO_BERRY, ITEM_NONE), ITEM_LUM_BERRY);
    EXPECT(BerryLedger_Has(ITEM_LUM_BERRY));
}

TEST("A neighbour with no recipe does not take the chance away from one that has it")
{
    // Cheri + Oran has no recipe; Cheri + Chesto does.
    EXPECT_EQ(HarvestMutationAfterPlanting(ITEM_CHERI_BERRY, ITEM_CHESTO_BERRY, ITEM_ORAN_BERRY), ITEM_LUM_BERRY);
}

TEST("Micle next to Custap only crosses into a Lansat after the League")
{
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(HarvestMutationAfterPlanting(ITEM_MICLE_BERRY, ITEM_CUSTAP_BERRY, ITEM_NONE), ITEM_NONE);
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(HarvestMutationAfterPlanting(ITEM_MICLE_BERRY, ITEM_CUSTAP_BERRY, ITEM_NONE), ITEM_LANSAT_BERRY);
    FlagClear(FLAG_SYS_GAME_CLEAR);
}
