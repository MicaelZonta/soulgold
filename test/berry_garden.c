#include "global.h"
#include "berry.h"
#include "berry_garden.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "item.h"
#include "list_menu.h"
#include "malloc.h"
#include "money.h"
#include "script_menu.h"
#include "test/test.h"
#include "constants/berry.h"
#include "constants/event_object_movement.h"
#include "constants/flags.h"
#include "constants/items.h"

// Berry Master's garden (.claude/berry_master/PLANO_DE_IMPLEMENTACAO.md,
// parts 2 to 11).

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

// Daily state (part 5).
TEST("The garden's day starts over once, when the daily flag was cleared")
{
    FlagClear(FLAG_DAILY_GARDEN_NEW_DAY);
    VarSet(VAR_GARDEN_TODAY, 0xFFFF);

    GardenRollDay();
    EXPECT_EQ(VarGet(VAR_GARDEN_TODAY), 0);
    EXPECT(FlagGet(FLAG_DAILY_GARDEN_NEW_DAY));

    // Same day: a second roll (another map load, another conversation) keeps it.
    GardenToday_Mark(GARDEN_TODAY_ORDER_ROLLED);
    GardenRollDay();
    EXPECT(GardenToday_Has(GARDEN_TODAY_ORDER_ROLLED));

    // Date change: ClearDailyFlags clears the flag, the next roll starts over.
    ClearDailyFlags();
    GardenRollDay();
    EXPECT(!GardenToday_Has(GARDEN_TODAY_ORDER_ROLLED));
}

TEST("Garden day bits are independent and nothing past bit 15 exists")
{
    VarSet(VAR_GARDEN_TODAY, 0);

    GardenToday_Mark(GARDEN_TODAY_ORDER_ROLLED);
    GardenToday_Mark(GARDEN_TODAY_TALKED_PEONY);
    GardenToday_Mark(GARDEN_TODAY_BIT_COUNT);

    EXPECT(GardenToday_Has(GARDEN_TODAY_ORDER_ROLLED));
    EXPECT(GardenToday_Has(GARDEN_TODAY_TALKED_PEONY));
    EXPECT(!GardenToday_Has(GARDEN_TODAY_ORDER_DONE));
    EXPECT(!GardenToday_Has(GARDEN_TODAY_BIT_COUNT));
    EXPECT_EQ(VarGet(VAR_GARDEN_TODAY), (1 << GARDEN_TODAY_ORDER_ROLLED) | (1 << GARDEN_TODAY_TALKED_PEONY));
}

// Garden levels (part 6).
static void SetUpGarden(u32 level, u32 bookSize, u32 money)
{
    ClearLedger();
    RegisterFirst(bookSize);
    VarSet(VAR_BERRY_GARDEN_LEVEL, level);
    VarSet(VAR_BERRY_GARDEN_WORK, GARDEN_WORK_NONE);
    VarSet(VAR_HARVEST_KING, 0);
    SetMoney(&gSaveBlock1Ptr->money, money);
    FlagSet(FLAG_DAILY_GARDEN_NEW_DAY); // today's roll already happened
}

TEST("Bram only offers the Proper Garden once the Book has 12")
{
    SetUpGarden(GARDEN_LEVEL_BACKYARD, 11, 99999);
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_NONE);

    SetUpGarden(GARDEN_LEVEL_BACKYARD, 12, 99999);
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_READY);
    EXPECT_EQ(gSpecialVar_0x8005, GARDEN_LEVEL_PROPER);

    SetUpGarden(GARDEN_LEVEL_NONE, 67, 99999); // before the tutorial
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_NONE);
}

TEST("Paying for a reform charges nothing when the money is short")
{
    SetUpGarden(GARDEN_LEVEL_BACKYARD, 12, 4999);
    EXPECT(!GardenReform_Pay());
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 4999);
    EXPECT_EQ(VarGet(VAR_BERRY_GARDEN_WORK), GARDEN_WORK_NONE);
}

TEST("A paid reform is built at the next date change, not today, and told once")
{
    SetUpGarden(GARDEN_LEVEL_BACKYARD, 12, 6000);
    EXPECT(GardenReform_Pay());
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), 1000);
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_BUILDING);

    // Same day: rolling again (another map load) builds nothing.
    GardenRollDay();
    EXPECT_EQ(VarGet(VAR_BERRY_GARDEN_LEVEL), GARDEN_LEVEL_BACKYARD);
    EXPECT_EQ(GardenReform_TakeBuiltLevel(), 0);

    ClearDailyFlags();
    GardenRollDay();
    EXPECT_EQ(VarGet(VAR_BERRY_GARDEN_LEVEL), GARDEN_LEVEL_PROPER);
    EXPECT_EQ(GardenGift_Count(), 3);
    EXPECT_EQ(GardenReform_TakeBuiltLevel(), GARDEN_LEVEL_PROPER);
    EXPECT_EQ(GardenReform_TakeBuiltLevel(), 0);
}

TEST("The channel and the Bug Hotel wait for Act 1; the Bug Hotel is free")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 22, 99999);
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_NEEDS_HELP);
    EXPECT(!GardenReform_Pay());
    VarSet(VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE);
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_READY);

    SetUpGarden(GARDEN_LEVEL_CHANNEL, 32, 0);
    VarSet(VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE);
    EXPECT(GardenReform_Pay());
    EXPECT_EQ(VarGet(VAR_BERRY_GARDEN_WORK), GARDEN_LEVEL_BUG_HOTEL);

    SetUpGarden(GARDEN_LEVEL_BUG_HOTEL, 67, 99999);
    VarSet(VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE);
    EXPECT_EQ(GardenReform_Check(), GARDEN_REFORM_NONE);
}

TEST("The channel waters the garden plots once a day, and not Laurel's plot")
{
    ClearBerryTrees();
    PlantBerryTree(BERRY_TREE_GARDEN_A1, ITEM_TO_BERRY(ITEM_ORAN_BERRY), BERRY_STAGE_PLANTED, TRUE);
    PlantBerryTree(BERRY_TREE_KINGS_PLOT, ITEM_TO_BERRY(ITEM_ORAN_BERRY), BERRY_STAGE_PLANTED, TRUE);
    VarSet(VAR_GARDEN_TODAY, 0);

    VarSet(VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_PROPER);
    GardenIrrigate();
    EXPECT_EQ((u32)GetBerryTreeInfo(BERRY_TREE_GARDEN_A1)->watered, 0);

    VarSet(VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_CHANNEL);
    GardenIrrigate();
    EXPECT_EQ((u32)GetBerryTreeInfo(BERRY_TREE_GARDEN_A1)->watered, 1 << 0);
    EXPECT_EQ((u32)GetBerryTreeInfo(BERRY_TREE_KINGS_PLOT)->watered, 0);
    EXPECT(GardenToday_Has(GARDEN_TODAY_WATERED));
}

TEST("The seed order lists every Berry in the Book but the Enigma, in item order")
{
    struct ListMenuItem *first, *last;

    ClearLedger();
    BerryLedger_RegisterStarters();
    BerryLedger_RegisterItem(ITEM_ENIGMA_BERRY);

    BerryLedger_BuildSeedMenu();
    EXPECT_EQ(MultichoiceDynamic_StackSize(), 8);
    first = MultichoiceDynamic_PeekElementAt(0);
    last = MultichoiceDynamic_PeekElementAt(7);
    EXPECT_EQ(first->id, ITEM_CHERI_BERRY);
    EXPECT_EQ(last->id, ITEM_PERSIM_BERRY);
    while (!MultichoiceDynamic_StackEmpty())
        Free((void *)MultichoiceDynamic_PopElement()->name);
    MultichoiceDynamic_DestroyStack();
}

// Debug menu (Berry Master...).
TEST("The debug Book sizes are exact, and only 67 includes the Enigma")
{
    static const u16 sizes[] = {0, 8, 11, 12, 22, 32, 60, 66, 67};
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sizes); i++)
    {
        gSpecialVar_0x8004 = sizes[i];
        BerryDebug_SetBook();
        EXPECT_EQ(BerryLedger_Count(), sizes[i]);
        if (sizes[i] >= 8)
            EXPECT(BerryLedger_Has(ITEM_PERSIM_BERRY));
        EXPECT_EQ(BerryLedger_Has(ITEM_ENIGMA_BERRY), sizes[i] == 67);
    }
}

// Today's order (part 7).
TEST("A Berry's recipe matches the crossing table, and Lansat waits for the League")
{
    u16 p1 = ITEM_NONE, p2 = ITEM_NONE;

    EXPECT(GetBerryRecipe(ITEM_AGUAV_BERRY, &p1, &p2));
    EXPECT((p1 == ITEM_RAWST_BERRY && p2 == ITEM_LEPPA_BERRY) || (p1 == ITEM_LEPPA_BERRY && p2 == ITEM_RAWST_BERRY));
    EXPECT(!GetBerryRecipe(ITEM_CHERI_BERRY, &p1, &p2));
    EXPECT(!GetBerryRecipe(ITEM_ENIGMA_BERRY, &p1, &p2));
    FlagClear(FLAG_SYS_GAME_CLEAR);
    EXPECT(!GetBerryRecipe(ITEM_LANSAT_BERRY, &p1, &p2));
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT(GetBerryRecipe(ITEM_LANSAT_BERRY, &p1, &p2));
    FlagClear(FLAG_SYS_GAME_CLEAR);
}

TEST("A discovery is never in the Book and both its parents are")
{
    u32 i;

    ClearLedger();
    BerryLedger_RegisterStarters();
    for (i = 0; i < 50; i++)
    {
        u16 item = BerryLedger_NextDiscovery();
        EXPECT(item != ITEM_NONE);
        EXPECT(!BerryLedger_Has(item));
        EXPECT(BerryLedger_Has(gSpecialVar_0x8005));
        EXPECT(BerryLedger_Has(gSpecialVar_0x8006));
    }
    RegisterFirst(67);
    EXPECT_EQ(BerryLedger_NextDiscovery(), ITEM_NONE);
}

TEST("The day's order is drawn once, paid once and drawn again the next day")
{
    u32 money;

    SetUpGarden(GARDEN_LEVEL_BACKYARD, 8, 0);
    VarSet(VAR_GARDEN_TODAY, 0);
    EXPECT_EQ(GardenOrder_Get(), GARDEN_ORDER_NONE);
    EXPECT(GardenOrder_Roll());
    EXPECT(!GardenOrder_Roll());
    EXPECT_EQ(GardenOrder_Get(), GARDEN_ORDER_OPEN);
    EXPECT(BerryLedger_Has(gSpecialVar_0x8004));   // level 1: always a common order
    EXPECT_EQ(gSpecialVar_0x8005, 3);               // Bram's eight are generation 0
    EXPECT_EQ(gSpecialVar_0x8007, FALSE);

    money = GetMoney(&gSaveBlock1Ptr->money);
    EXPECT_EQ(GardenOrder_Pay(), 300);              // 3 x 100
    EXPECT_EQ(GetMoney(&gSaveBlock1Ptr->money), money + 300);
    EXPECT_EQ(GardenOrder_Get(), GARDEN_ORDER_DONE);
    EXPECT_EQ(GardenOrder_Pay(), 0);                // never twice

    ClearDailyFlags();
    GardenRollDay();
    EXPECT_EQ(GardenOrder_Get(), GARDEN_ORDER_NONE);
    EXPECT(GardenOrder_Roll());
    EXPECT_EQ(GardenOrder_Get(), GARDEN_ORDER_OPEN);
}

TEST("A discovery order asks for one Berry, pays double and gives Surprise Mulch")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 8, 0);
    VarSet(VAR_GARDEN_TODAY, 0);
    gSpecialVar_0x8004 = TRUE;
    BerryDebug_NewOrder();
    EXPECT(GardenOrder_Roll());
    EXPECT_EQ(GardenOrder_Get(), GARDEN_ORDER_OPEN);
    EXPECT_EQ(gSpecialVar_0x8007, TRUE);
    EXPECT_EQ(gSpecialVar_0x8005, 1);
    EXPECT(!BerryLedger_Has(gSpecialVar_0x8004));
    EXPECT_EQ(GardenOrder_RewardMulch(), ITEM_SURPRISE_MULCH);
    EXPECT_EQ(GardenOrder_Pay(), 300);              // generation 1: 1 x 150 x 2
}

// Part 8: who is where (section 2.1 / 14.3).
#define PLACE(who, period, day) GardenCast_PlaceOf(GARDEN_CAST_##who, GARDEN_PERIOD_##period, WEEKDAY_##day, TRUE, HARVEST_KING_ACT1_DONE)

TEST("The game's evening counts as the garden's night")
{
    EXPECT_EQ(GardenCast_PeriodOf(TIME_MORNING), GARDEN_PERIOD_MORNING);
    EXPECT_EQ(GardenCast_PeriodOf(TIME_DAY), GARDEN_PERIOD_DAY);
    EXPECT_EQ(GardenCast_PeriodOf(TIME_EVENING), GARDEN_PERIOD_NIGHT);
    EXPECT_EQ(GardenCast_PeriodOf(TIME_NIGHT), GARDEN_PERIOD_NIGHT);
}

TEST("Bram waters in the morning and is home the rest of the day")
{
    EXPECT_EQ(PLACE(BRAM, MORNING, MON), GARDEN_PLACE_GARDEN);
    EXPECT_EQ(PLACE(BRAM, DAY, MON), GARDEN_PLACE_HOUSE);
    EXPECT_EQ(PLACE(BRAM, NIGHT, SAT), GARDEN_PLACE_HOUSE);
}

TEST("Before the tutorial Bram is in the house at any hour")
{
    EXPECT_EQ(GardenCast_PlaceOf(GARDEN_CAST_BRAM, GARDEN_PERIOD_MORNING, WEEKDAY_MON, FALSE, 0), GARDEN_PLACE_HOUSE);
}

TEST("Laurel is in the garden on weekday afternoons and bakes at home on weekends")
{
    EXPECT_EQ(PLACE(LAUREL, MORNING, WED), GARDEN_PLACE_HOUSE);
    EXPECT_EQ(PLACE(LAUREL, DAY, WED), GARDEN_PLACE_GARDEN);
    EXPECT_EQ(PLACE(LAUREL, DAY, SUN), GARDEN_PLACE_HOUSE);
    EXPECT_EQ(PLACE(LAUREL, NIGHT, WED), GARDEN_PLACE_HOUSE);
}

TEST("Tilly only comes on weekends and goes home at night")
{
    EXPECT_EQ(PLACE(TILLY, DAY, FRI), GARDEN_PLACE_AWAY);
    EXPECT_EQ(PLACE(TILLY, MORNING, SAT), GARDEN_PLACE_HOUSE);
    EXPECT_EQ(PLACE(TILLY, DAY, SUN), GARDEN_PLACE_GARDEN);
    EXPECT_EQ(PLACE(TILLY, NIGHT, SAT), GARDEN_PLACE_AWAY);
}

TEST("Bugsy comes on Tuesday and Thursday afternoons from Act 1b on")
{
    EXPECT_EQ(PLACE(BUGSY, DAY, TUE), GARDEN_PLACE_GARDEN);
    EXPECT_EQ(PLACE(BUGSY, DAY, THU), GARDEN_PLACE_GARDEN);
    EXPECT_EQ(PLACE(BUGSY, MORNING, TUE), GARDEN_PLACE_AWAY);
    EXPECT_EQ(PLACE(BUGSY, DAY, WED), GARDEN_PLACE_AWAY);
    EXPECT_EQ(GardenCast_PlaceOf(GARDEN_CAST_BUGSY, GARDEN_PERIOD_DAY, WEEKDAY_TUE, TRUE, HARVEST_KING_BUGSY_CAME - 1), GARDEN_PLACE_AWAY);
}

TEST("Tilly and Bugsy are never in the garden together")
{
    u32 day, period;

    for (day = WEEKDAY_SUN; day <= WEEKDAY_SAT; day++)
    {
        for (period = GARDEN_PERIOD_MORNING; period <= GARDEN_PERIOD_NIGHT; period++)
        {
            EXPECT(GardenCast_PlaceOf(GARDEN_CAST_TILLY, period, day, TRUE, HARVEST_KING_ACT1_DONE) != GARDEN_PLACE_GARDEN
                || GardenCast_PlaceOf(GARDEN_CAST_BUGSY, period, day, TRUE, HARVEST_KING_ACT1_DONE) != GARDEN_PLACE_GARDEN);
        }
    }
}

// Part 9: hearts, line banks and Bram's news (section 14.3, 9.8).
TEST("A heart a day: only the first talk of the day counts")
{
    VarSet(VAR_GARDEN_HEARTS, 0);
    VarSet(VAR_GARDEN_TODAY, 0);
    gSpecialVar_0x8004 = GARDEN_HEARTS_LAUREL;
    EXPECT(GardenHearts_Talk());
    gSpecialVar_0x8004 = GARDEN_HEARTS_LAUREL;
    EXPECT(!GardenHearts_Talk());
    EXPECT_EQ(GardenHearts_Get(GARDEN_HEARTS_LAUREL), 1);
    EXPECT_EQ(GardenHearts_Get(GARDEN_HEARTS_BRAM), 0);   // nibbles do not leak
    VarSet(VAR_GARDEN_TODAY, 0);                          // the next day
    gSpecialVar_0x8004 = GARDEN_HEARTS_LAUREL;
    EXPECT(GardenHearts_Talk());
    EXPECT_EQ(GardenHearts_Get(GARDEN_HEARTS_LAUREL), 2);
}

TEST("Hearts stop at 15 and open the lines at 5 and 12 days")
{
    u32 day;

    VarSet(VAR_GARDEN_HEARTS, 0);
    EXPECT_EQ(GardenLine_Count(GARDEN_HEARTS_TILLY), 4);
    for (day = 1; day <= 20; day++)
    {
        VarSet(VAR_GARDEN_TODAY, 0);
        gSpecialVar_0x8004 = GARDEN_HEARTS_TILLY;
        GardenHearts_Talk();
        if (day == GARDEN_HEARTS_TIER1_DAYS)
            EXPECT_EQ(GardenLine_Count(GARDEN_HEARTS_TILLY), 7);
        if (day == GARDEN_HEARTS_TIER2_DAYS)
            EXPECT_EQ(GardenLine_Count(GARDEN_HEARTS_TILLY), 10);
    }
    EXPECT_EQ(GardenHearts_Get(GARDEN_HEARTS_TILLY), GARDEN_HEARTS_MAX);
    EXPECT_EQ(GardenHearts_Get(GARDEN_HEARTS_PEONY), 0);
    EXPECT_EQ(GardenLine_Count(GARDEN_HEARTS_NONE), 10);
}

TEST("The line of the day is the same all day and moves with the days")
{
    VarSet(VAR_GARDEN_HEARTS, 0);
    VarSet(VAR_DAYS, 6);
    gSpecialVar_0x8004 = GARDEN_HEARTS_BRAM;
    EXPECT_EQ(GardenLine_Pick(), 2);                      // 6 % 4
    gSpecialVar_0x8004 = GARDEN_HEARTS_NONE;
    EXPECT_EQ(GardenLine_Pick(), 6);                      // 6 % 10
    VarSet(VAR_DAYS, 7);
    gSpecialVar_0x8004 = GARDEN_HEARTS_BRAM;
    EXPECT_EQ(GardenLine_Pick(), 3);
}

TEST("Bram celebrates the first garden harvest once, then each new Berry")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 8, 0);
    VarSet(VAR_GARDEN_NEWS, 0);
    BerryLedger_RegisterHarvest(BERRY_TREE_ROUTE_30_PECHA, ITEM_LUM_BERRY); // a route tree: no news
    EXPECT_EQ(GardenNews_Take(), GARDEN_NEWS_NONE);
    EXPECT(BerryLedger_Has(ITEM_LUM_BERRY));               // still in the Book

    ClearLedger();
    RegisterFirst(8);
    BerryLedger_RegisterHarvest(BERRY_TREE_GARDEN_A1, ITEM_ORAN_BERRY); // a starter in the garden
    BerryLedger_RegisterHarvest(BERRY_TREE_GARDEN_A2, ITEM_LUM_BERRY);  // a cross, new
    EXPECT_EQ(GardenNews_Take(), GARDEN_NEWS_FIRST_HARVEST);
    EXPECT_EQ(GardenNews_Take(), GARDEN_NEWS_NEW_BERRY);
    EXPECT_EQ(gSpecialVar_0x8004, ITEM_LUM_BERRY);
    EXPECT_EQ(GardenNews_Take(), GARDEN_NEWS_NONE);

    BerryLedger_RegisterHarvest(BERRY_TREE_GARDEN_A3, ITEM_LUM_BERRY);  // not new any more
    EXPECT_EQ(GardenNews_Take(), GARDEN_NEWS_NONE);               // and no second "first"
}

// Part 10: pests (section 7.2).
TEST("Pests only on the ten garden plots")
{
    EXPECT(IsBerryGardenTree(BERRY_TREE_GARDEN_A1));
    EXPECT(IsBerryGardenTree(BERRY_TREE_GARDEN_B4));
    EXPECT(!IsBerryGardenTree(BERRY_TREE_KINGS_PLOT));
    EXPECT(!IsBerryGardenTree(BERRY_TREE_ROUTE_30_PECHA));
}

TEST("The colour picks the row and the hour the common pest")
{
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 0, ITEM_NONE, 0, FALSE), SPECIES_LEDYBA);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, TRUE, 0, ITEM_NONE, 0, FALSE), SPECIES_SPINARAK);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_BLUE, FALSE, 0, ITEM_NONE, 0, FALSE), SPECIES_BLIPBUG);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_BLUE, TRUE, 0, ITEM_NONE, 0, FALSE), SPECIES_VOLBEAT);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_PURPLE, TRUE, 0, ITEM_NONE, 0, FALSE), SPECIES_VOLBEAT); // shares blue
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_PINK, TRUE, 0, ITEM_NONE, 0, FALSE), SPECIES_ILLUMISE);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_YELLOW, FALSE, 0, ITEM_NONE, 0, FALSE), SPECIES_COMBEE);
}

TEST("The Berry's generation makes the uncommon and the rare pests likelier")
{
    // generation 0-1: 70 / 27 / 3
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 1, ITEM_NONE, 69, FALSE), SPECIES_LEDYBA);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 1, ITEM_NONE, 70, FALSE), SPECIES_WURMPLE);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 1, ITEM_NONE, 97, FALSE), SPECIES_HERACROSS);
    // generation 4+: 30 / 40 / 30
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 4, ITEM_NONE, 30, FALSE), SPECIES_WURMPLE);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 4, ITEM_NONE, 70, FALSE), SPECIES_HERACROSS);
}

TEST("Mulch brings Rellor or Dwebble half of the time")
{
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 0, ITEM_GOOEY_MULCH, 0, TRUE), SPECIES_RELLOR);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 0, ITEM_RICH_MULCH, 0, TRUE), SPECIES_RELLOR);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 0, ITEM_STABLE_MULCH, 0, TRUE), SPECIES_DWEBBLE);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 0, ITEM_STABLE_MULCH, 0, FALSE), SPECIES_LEDYBA);
    EXPECT_EQ(GardenPest_Pick(BERRY_COLOR_RED, FALSE, 0, ITEM_GROWTH_MULCH, 0, TRUE), SPECIES_LEDYBA);
}

TEST("The Bug Hotel doubles the pest chance")
{
    VarSet(VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_CHANNEL);
    EXPECT_EQ(GardenPest_Chance(), 15);
    VarSet(VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_BUG_HOTEL);
    EXPECT_EQ(GardenPest_Chance(), 30);
}

// Part 11: Klara's raid (section 13.4).
static void PlantRipe(u32 id)
{
    struct BerryTree *tree = GetBerryTreeInfo(id);

    tree->berry = ItemIdToBerryType(ITEM_PECHA_BERRY);
    tree->stage = BERRY_STAGE_BERRIES;
    tree->berryYield = 3;
}

TEST("Klara left waiting takes her plot and Bram has a line for it")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 8, 0);
    VarSet(VAR_GARDEN_TODAY, 1 << GARDEN_TODAY_KLARA_COMES);
    PlantRipe(BERRY_TREE_GARDEN_A3);
    VarSet(VAR_GARDEN_RIVALS, 0x0010 | (2 << 5));     // waiting, plot A3
    gSpecialVar_0x8004 = LOCALID_ROUTE30_KLARA;
    EXPECT(!GardenKlara_Place());
    EXPECT_EQ((u32)GetBerryTreeInfo(BERRY_TREE_GARDEN_A3)->stage, BERRY_STAGE_NO_BERRY);
    EXPECT(GardenToday_Has(GARDEN_TODAY_KLARA_RESOLVED));
    EXPECT(GardenKlara_TakeBramLine() >= 1);
    EXPECT_EQ(GardenKlara_TakeBramLine(), 0);           // said once
}

TEST("Beating Klara keeps the plot, counts a win and Bram cheers")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 8, 0);
    VarSet(VAR_GARDEN_TODAY, 1 << GARDEN_TODAY_KLARA_COMES);
    PlantRipe(BERRY_TREE_GARDEN_B1);
    VarSet(VAR_GARDEN_RIVALS, 4 | 0x0010 | (6 << 5)); // 4 wins, waiting, plot B1
    gSpecialVar_0x8004 = TRUE;
    gSpecialVar_0x8005 = 0;
    EXPECT_EQ(GardenKlara_Resolve(), 5);               // the 5th: the mochi line
    EXPECT_EQ((u32)GetBerryTreeInfo(BERRY_TREE_GARDEN_B1)->stage, BERRY_STAGE_BERRIES);
    EXPECT(GardenToday_Has(GARDEN_TODAY_KLARA_RESOLVED));
    EXPECT_EQ(GardenKlara_TakeBramLine(), 5);
    gSpecialVar_0x8004 = LOCALID_ROUTE30_KLARA;
    EXPECT(!GardenKlara_Place());                       // resolved: not again today
}

TEST("Losing to Klara empties her plot")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 8, 0);
    PlantRipe(BERRY_TREE_GARDEN_A1);
    VarSet(VAR_GARDEN_RIVALS, 0x0010);                 // waiting, plot A1
    gSpecialVar_0x8004 = FALSE;
    gSpecialVar_0x8005 = 2;
    EXPECT_EQ(GardenKlara_Resolve(), 0);
    EXPECT_EQ((u32)GetBerryTreeInfo(BERRY_TREE_GARDEN_A1)->stage, BERRY_STAGE_NO_BERRY);
    EXPECT_EQ(GardenKlara_TakeBramLine(), 3);
}

TEST("Klara only comes when the morning was drawn")
{
    SetUpGarden(GARDEN_LEVEL_PROPER, 8, 0);
    VarSet(VAR_GARDEN_TODAY, 0);
    VarSet(VAR_GARDEN_RIVALS, 0);
    PlantRipe(BERRY_TREE_GARDEN_A1);
    gSpecialVar_0x8004 = LOCALID_ROUTE30_KLARA;
    EXPECT(!GardenKlara_Place());
}
