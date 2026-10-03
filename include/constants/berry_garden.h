#ifndef GUARD_CONSTANTS_BERRY_GARDEN_H
#define GUARD_CONSTANTS_BERRY_GARDEN_H

// Berry Master's garden on Route 30 (.claude/berry_master/REI_DA_COLHEITA.md).
//
// Shared by C (src/berry_garden.c) and scripts (data/maps/Route30*/scripts.inc),
// so only plain #defines here.

// VAR_GARDEN_TODAY: what already happened in the garden today, one bit each
// (section 14.6). The whole var is zeroed by GardenRollDay the first time the
// garden is touched on a new day. Scripts ask with
//     setvar VAR_0x8004, GARDEN_TODAY_<X>
//     specialvar VAR_RESULT, GardenToday_Check    @ or: special GardenToday_Set
// The part of the plan that first uses each bit is in brackets.
#define GARDEN_TODAY_ORDER_ROLLED    0   // today's order was drawn (part 7)
#define GARDEN_TODAY_ORDER_DONE      1   // today's order was delivered (part 7)
#define GARDEN_TODAY_WATERED         2   // the level-3 channel watered the garden (part 6)
#define GARDEN_TODAY_KLARA_COMES     3   // Klara raids this morning (part 11)
#define GARDEN_TODAY_KLARA_RESOLVED  4   // the raid is over, won or lost (part 11)
#define GARDEN_TODAY_FOUGHT_TILLY    5   // (part 11)
#define GARDEN_TODAY_FOUGHT_BUGSY    6   // (part 11)
#define GARDEN_TODAY_FOUGHT_AVERY    7   // (part 16)
#define GARDEN_TODAY_FOUGHT_PEONY    8   // (part 13)
#define GARDEN_TODAY_FOUGHT_PEONIA   9   // Peonia, alone or with Tilly (part 16)
#define GARDEN_TODAY_MUSTARD_COMES   10  // Mustard visits today (part 16)
#define GARDEN_TODAY_FOUGHT_MUSTARD  11  // (part 16)
#define GARDEN_TODAY_TALKED_BRAM     12  // hearts: one a day per person (part 9)
#define GARDEN_TODAY_TALKED_LAUREL   13
#define GARDEN_TODAY_TALKED_TILLY    14
#define GARDEN_TODAY_TALKED_PEONY    15
#define GARDEN_TODAY_BIT_COUNT       16  // VAR_GARDEN_TODAY is a u16: nothing past 15

// VAR_BERRY_GARDEN_LEVEL (section 5). 0 until Bram's tutorial.
#define GARDEN_LEVEL_NONE            0
#define GARDEN_LEVEL_BACKYARD        1   // bed A; the tutorial
#define GARDEN_LEVEL_PROPER          2   // bed B, 3 Berries a day, seed order
#define GARDEN_LEVEL_CHANNEL         3   // the garden wakes up watered
#define GARDEN_LEVEL_BUG_HOTEL       4   // more pests, rarer ones (part 10)
#define GARDEN_LEVEL_KINGS           5   // Laurel's plot, epilogue (part 16)
#define GARDEN_LEVEL_LAST_REFORM     GARDEN_LEVEL_BUG_HOTEL  // Bram builds up to here

// VAR_BERRY_GARDEN_WORK: level paid (being built) or level + GARDEN_WORK_BUILT
// (built; Bram has not talked about it yet).
#define GARDEN_WORK_NONE             0
#define GARDEN_WORK_BUILT            10

// GardenReform_Check, what Bram can offer now. VAR_0x8005 = the next level.
#define GARDEN_REFORM_NONE           0   // nothing to offer: done, or the Book is short
#define GARDEN_REFORM_BUILDING       1   // already paid, done by tomorrow
#define GARDEN_REFORM_NEEDS_HELP     2   // Book is enough, but the story is not there yet
#define GARDEN_REFORM_READY          3   // can be paid now

// Today's order (section 6), GardenOrder_Get.
#define GARDEN_ORDER_NONE            0   // nothing to deliver today (no Book yet)
#define GARDEN_ORDER_OPEN            1
#define GARDEN_ORDER_DONE            2

// Who placed the order (section 14.4 Q): only the first line of Bram's text.
#define GARDEN_CLIENT_KURT           0
#define GARDEN_CLIENT_FLOWER_SHOP    1
#define GARDEN_CLIENT_NURSE          2
#define GARDEN_CLIENT_MOOMOO_FARM    3
#define GARDEN_CLIENT_DAY_CARE       4
#define GARDEN_CLIENT_BUGSY          5   // story state >= 3; Kurt before that
#define GARDEN_CLIENT_THEATER        6
#define GARDEN_CLIENT_LIGHTHOUSE     7
#define GARDEN_CLIENT_SCHOOL         8
#define GARDEN_CLIENT_LAUREL         9
#define GARDEN_CLIENT_COUNT          10

// VAR_HARVEST_KING, the "Harvest King" story (section 8.1; part 12 writes
// 0..8, part 13 on the rest). Nothing in the garden routine stops on it.
#define HARVEST_KING_NONE            0   // before Bram's tutorial
#define HARVEST_KING_PROLOGUE        1   // "Not the patch by the door." (8.2)
#define HARVEST_KING_VISITORS        2   // the first pest beaten or caught (8.3)
#define HARVEST_KING_BUGSY_CAME      3   // Act 1b: Bugsy is around (8.4)
#define HARVEST_KING_ACT1_DONE       4   // Act 1c, the census: levels 3 and 4 open (8.5)
#define HARVEST_KING_FOOTPRINTS      5   // Act 2: the night visitor seen (8.6)
#define HARVEST_KING_BRAM_TOLD       6   // Act 2b: Bram told about the seed (8.7)
#define HARVEST_KING_NOTEBOOK        7   // Act 3: Laurel gave the Enigma (8.8)
#define HARVEST_KING_FIRST_LEAF      8   // Act 4: the Enigma came up (8.9)
#define HARVEST_KING_KING_CAME       9   // Act 5: Calyrex, Peony and Peonia (13.3, 14.2)
#define HARVEST_KING_ICEROOT         10  // Act 5b: the Iceroot seed planted (14.2)
#define HARVEST_KING_SHADEROOT       11  // Act 5b: the Shaderoot seed planted
#define HARVEST_KING_GUESTS_LEAVE    15  // Peony and Peonia are guests up to here (14.2)

// One-time story lines (GardenStory_Check / _Mark), said once in the game.
#define GARDEN_STORY_BRAM_BUGS       0   // Bram after Act 1a: "BUGS? In MY beds?"
#define GARDEN_STORY_LAUREL_HEARD    1   // Laurel the morning after Act 2
#define GARDEN_STORY_WROTE_HOME      2   // Laurel the night after Act 4
#define GARDEN_STORY_CARROT_PLANTED  3   // Act 5b: a seed went into Laurel's plot
#define GARDEN_STORY_CARROT_READY    4   // a new day came since: the carrot can be pulled at night
#define GARDEN_STORY_LAUREL_PICKED   5   // Laurel the morning after: "You picked."
#define GARDEN_STORY_COUNT           7

// Act 1c: how many garden-only families Bugsy wants caught.
#define GARDEN_CENSUS_FAMILIES       3

// Every Berry in the Book but the Enigma (the title, section 3.4): nothing
// left that grows from a cross. With Lansat and Starf locked before the League
// the Book stops at 65, so 66 always means "the notebook is done".
#define BERRY_LEDGER_ALL_GROWN       66

// The routine (part 8, section 2.1). Periods follow the game's clock
// (GetTimeOfDay, OW_TIMES_OF_DAY): evening counts as night.
#define GARDEN_PERIOD_MORNING        0
#define GARDEN_PERIOD_DAY            1
#define GARDEN_PERIOD_NIGHT          2

#define GARDEN_CAST_BRAM             0
#define GARDEN_CAST_LAUREL           1
#define GARDEN_CAST_TILLY            2
#define GARDEN_CAST_BUGSY            3
#define GARDEN_CAST_PEONY            4   // guest, story states 9..14 (part 13)
#define GARDEN_CAST_PEONIA           5

#define GARDEN_PLACE_AWAY            0
#define GARDEN_PLACE_GARDEN          1   // Route30
#define GARDEN_PLACE_HOUSE           2   // Route30_House

// Klara's object on Route30 (part 11): her position is set by GardenKlara_Place.
// Route30_House (Bram's and Laurel's scripts run on both maps).
#define LOCALID_HOUSE_BRAM           1
#define LOCALID_HOUSE_SUNFLORA       4
#define LOCALID_ROUTE30_BRAM         34
#define LOCALID_ROUTE30_LAUREL       35
#define LOCALID_ROUTE30_BUGSY        37
#define LOCALID_ROUTE30_KLARA        38
#define LOCALID_ROUTE30_SPECTRIER    39  // Act 2's night visitor (part 12)
#define LOCALID_ROUTE30_PEONY        40  // part 13
#define LOCALID_ROUTE30_CALYREX      41
#define LOCALID_ROUTE30_PEONIA       42
#define LOCALID_ROUTE30_KINGS_PLOT   22
#define LOCALID_HOUSE_PEONY          5
#define LOCALID_HOUSE_PEONIA         6
// The ten garden trees on Route30 are objects 24..33, in plot order (A1..B4).
#define LOCALID_ROUTE30_GARDEN_A1    24

// Hearts (part 9, section 14.3): days the player talked to them, 0..15, in
// VAR_GARDEN_HEARTS, 4 bits each, and one GARDEN_TODAY_TALKED_* bit each.
// GardenLine_Pick takes one of these too; GARDEN_HEARTS_NONE = a bank of 10
// with no hearts (Bugsy, Laurel's notebook, Bram's gift, dreams...).
#define GARDEN_HEARTS_BRAM           0
#define GARDEN_HEARTS_LAUREL         1
#define GARDEN_HEARTS_TILLY          2
#define GARDEN_HEARTS_PEONY          3
#define GARDEN_HEARTS_NONE           4
#define GARDEN_HEARTS_MAX            15
#define GARDEN_HEARTS_TIER1_DAYS     5   // lines 5-7 open
#define GARDEN_HEARTS_TIER2_DAYS     12  // lines 8-10 open

// What Bram has to tell on the next talk (GardenNews_Take).
#define GARDEN_NEWS_NONE             0
#define GARDEN_NEWS_FIRST_HARVEST    1   // the first Berry picked in the garden
#define GARDEN_NEWS_NEW_BERRY        2   // a Berry new to the Book grew in the garden; VAR_0x8004 = it

#endif // GUARD_CONSTANTS_BERRY_GARDEN_H
