#ifndef GUARD_BERRY_GARDEN_H
#define GUARD_BERRY_GARDEN_H

#include "constants/berry_garden.h"
#include "constants/rtc.h"

// Berry Master's garden on Route 30 (.claude/berry_master/REI_DA_COLHEITA.md).

// Book of Berries: TRUE when the player has ever harvested this Berry.
bool32 BerryLedger_Has(u16 itemId);
// Called from ObjectEventInteractionPickBerryTree for every Berry that
// actually went into the bag. Not a Berry: ignored.
void BerryLedger_RegisterItem(u16 itemId);
// The same for a Berry picked from a tree, plus what Bram will say about it
// (first garden harvest, a Berry new to the Book grown in the garden).
void BerryLedger_RegisterHarvest(u32 treeId, u16 itemId);

// Specials (data/specials.inc)
void BerryLedger_Register(void);
void BerryLedger_RegisterStarters(void);
u16 BerryLedger_Count(void);
u16 BerryLedger_RandomRegistered(void);
u16 BerryLedger_RandomRegisteredRare(void);
u16 BerryLedger_PendingMilestone(void);

// Daily state (VAR_GARDEN_TODAY, one GARDEN_TODAY_* bit each).
bool32 GardenToday_Has(u32 bit);
void GardenToday_Mark(u32 bit);

// Specials (data/specials.inc)
void GardenRollDay(void);
u16 GardenToday_Check(void);
void GardenToday_Set(void);
u16 GardenReform_Check(void);
u16 GardenReform_Pay(void);
u16 GardenReform_TakeBuiltLevel(void);
void GardenIrrigate(void);
u16 GardenGift_Count(void);
void BerryLedger_BuildSeedMenu(void);
u16 BerryLedger_NextDiscovery(void);
u16 BerryLedger_GetRecipe(void);
u16 GardenOrder_Roll(void);
u16 GardenOrder_Get(void);
u16 GardenOrder_RewardMulch(void);
u16 GardenOrder_Pay(void);
void GardenCast_Apply(void);
u16 GardenCast_IsWeekend(void);
u16 MollyCast_Place(void);
u32 MollyCast_PlaceOf(u32 period, u32 weekday, bool32 storyDone);
u16 GardenHearts_Talk(void);
u16 GardenLine_Pick(void);
u16 GardenNews_Take(void);
u16 GardenLead_IsType(void);
u16 GardenPlots_Planted(void);

u16 GardenPest_IsGardenTree(void);
u16 GardenWeeds_Bed(void);
u16 GardenPests_AllCaught(void);
u16 GardenKlara_Place(void);
u16 GardenKlara_Resolve(void);
u16 GardenKlara_TakeBramLine(void);
u16 GardenTilly_PrizeMulch(void);
u16 GardenStory_Check(void);
void GardenStory_Mark(void);
u16 GardenKingsPlot_Stage(void);
u16 GardenPlots_HaveEnigma(void);
u16 GardenPests_FamiliesCaught(void);
u16 GardenPest_LastSpecies(void);
void GardenKingsPlot_Empty(void);
u8 GardenKingsPlot_Yield(const struct BerryTree *tree, u8 yield);
u16 GardenTree_IsKingsPlot(void);
u16 BerryLedger_HasTitle(void);
bool32 GardenSteed_NexusEligible(u16 species);

// Story places in another light (parts 14-15): src/fieldmap.c and
// src/overworld.c tint the map palettes while MapTint_Mode() is not NONE.
u32 MapTint_Mode(void);
void MapTint_Apply(u16 *pal, u32 count);
void MapTint_ApplyToBg(u32 firstColor, u32 count);
void GreenfieldCrystal_Tint(u16 *pal, u32 count);

// Pests and weeds (part 10): only garden plots (src/berry.c asks these).
bool32 IsBerryGardenTree(u32 treeId);
u32 GardenPest_Chance(void);
u16 GardenPest_Species(u32 treeId);
u8 GardenPest_Level(u16 species);
u16 GardenPest_Pick(u32 color, bool32 night, u32 generation, u16 mulchItem, u32 roll, bool32 mulchRoll);

// Hearts and line banks as pure rules (tests).
u32 GardenHearts_Get(u32 who);
u32 GardenLine_Count(u32 who);

// The routine as pure rules (tests): GARDEN_PERIOD_* of a TimeOfDay, and the
// GARDEN_PLACE_* of a GARDEN_CAST_* member at that period and weekday.
u32 GardenCast_PeriodOf(enum TimeOfDay timeOfDay);
u32 GardenCast_PlaceOf(u32 who, u32 period, u32 weekday, bool32 tutorialDone, u32 harvestKing);

// Debug menu (Berry Master...)
void BerryDebug_AdvanceHours(void);
void BerryDebug_AdvanceToMorning(void);
void BerryDebug_ReloadMap(void);
void BerryDebug_SetBook(void);
void BerryDebug_SetLevel(void);
void BerryDebug_RipenGarden(void);
void BerryDebug_GrowGarden(void);
void BerryDebug_EmptyGarden(void);
void BerryDebug_ResetToday(void);
void BerryDebug_ResetAll(void);
void BerryDebug_ClearMoney(void);
void BerryDebug_Status(void);
void BerryDebug_NewOrder(void);
void BerryDebug_SetHearts(void);
void BerryDebug_KlaraComes(void);
void BerryDebug_SetStory(void);
void BerryDebug_KingsPlotSprout(void);

#endif // GUARD_BERRY_GARDEN_H
