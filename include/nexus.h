#ifndef GUARD_NEXUS_H
#define GUARD_NEXUS_H

#include "constants/nexus.h"

// One trainer of the pool. Content lives in src/data/nexus/trainers.h.
struct NexusTrainer
{
    u16 trainerId;              // TRAINER_NEXUS_*: its own flag, scaled by R2
    u16 graphicsId;             // overworld sprite shown at the door
    const u8 *fightScript;      // R16 generic lines (rooms 1-4), data/scripts/nexus.inc
};

// One legendary of the pool. Content lives in src/data/nexus/legendaries.h.
struct NexusLegendary
{
    u16 species;
    u16 champion;               // NEXUS_TRAINER_* index into gNexusTrainers
    const u8 *championScript;   // R16 lines about THIS legendary (champion room); a trainer
                                 // who champions more than one legendary gets one script per
                                 // legendary here, never a single script on gNexusTrainers
    bool8 requiresCaught;       // R1: only drawn once the player caught it outside the Nexus
    u8 bossBars;                // R6: setbossbattle parameters
    u8 bossStatMultiplier;
    u8 bossPhaseProfile;
    const u8 *afterBossScript;  // optional extra after the fragment is caught, or NULL
    const u8 *lookerFileScript; // R18: the Looker File notebook in the champion room, or NULL
};

// One prize group (R9). Content lives in src/data/nexus/prizes.h.
struct NexusPrizeGroup
{
    u16 firstItem;              // a run of consecutive item ids: firstItem .. firstItem + count - 1
    u16 count;
    u8 weight;                  // relative chance of this group
};

extern const struct NexusTrainer gNexusTrainers[];
extern const struct NexusLegendary gNexusLegendaries[];

bool32 Nexus_IsNexusTrainer(u16 trainerId);

#endif // GUARD_NEXUS_H
