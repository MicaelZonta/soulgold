#ifndef GUARD_BERRY_GARDEN_H
#define GUARD_BERRY_GARDEN_H

#include "constants/berry_garden.h"

// Berry Master's garden on Route 30 (.claude/berry_master/REI_DA_COLHEITA.md).

// Book of Berries: TRUE when the player has ever harvested this Berry.
bool32 BerryLedger_Has(u16 itemId);
// Called from ObjectEventInteractionPickBerryTree for every Berry that
// actually went into the bag. Not a Berry: ignored.
void BerryLedger_RegisterItem(u16 itemId);

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

#endif // GUARD_BERRY_GARDEN_H
