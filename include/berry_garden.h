#ifndef GUARD_BERRY_GARDEN_H
#define GUARD_BERRY_GARDEN_H

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

#endif // GUARD_BERRY_GARDEN_H
