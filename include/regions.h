#ifndef GUARD_REGIONS_H
#define GUARD_REGIONS_H

#include "global.h"
#include "constants/regions.h"

static inline u32 GetCurrentRegion(void)
{
    // TODO: Since there's no current multi-region support, we have this constant for the purposes of regional form comparisons.
    return REGION_HOENN;
}

// Map-section based tests for the player's current map (src/regions.c).
// SoulGold's world has two halves: Kanto (KANTO_MAPSEC_START..END) and
// everything else, which is Johto.
bool8 IsMapSectionInKanto(u32 mapSecId);
bool8 IsPlayerInKanto(void);
bool8 IsPlayerInJohto(void);

#endif // GUARD_REGIONS_H
