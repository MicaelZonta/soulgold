#ifndef GUARD_CONSTANTS_NEXUS_H
#define GUARD_CONSTANTS_NEXUS_H

// Nexus (Rift Missions post-game loop). Rules: .claude/rift_missions/nexus/NEXUS_REGRAS.md
// Implementation: .claude/rift_missions/nexus/NEXUS_IMPLEMENTATION.md
//
// Shared by C (src/nexus.c) and scripts (data/maps/Nexus/scripts.inc), so
// only plain #defines here.

// R5: the shape of a Daily run.
#define NEXUS_TRAINER_ROOMS         4   // rooms with a choice of trainers
#define NEXUS_DOORS_PER_ROOM        3   // R5.1: three teleports per room
#define NEXUS_ROOM_CHAMPION         NEXUS_TRAINER_ROOMS         // 4: the champion of the legendary
#define NEXUS_ROOM_BOSS             (NEXUS_TRAINER_ROOMS + 1)   // 5: the legendary itself
#define NEXUS_ROOM_COUNT            (NEXUS_TRAINER_ROOMS + 2)

// Doors, in map order: west arm, north arm, east arm. The champion room uses
// only the north door.
#define NEXUS_DOOR_WEST             0
#define NEXUS_DOOR_NORTH            1
#define NEXUS_DOOR_EAST             2
#define NEXUS_DOOR_CHAMPION         NEXUS_DOOR_NORTH
#define NEXUS_DOOR_NONE             3   // R15: "not chosen yet" in a 2-bit field

// R15: VAR_NEXUS_DAILY progress field. 0..5 = fights won (4 trainers +
// champion), 6 = legendary beaten and its fragment waiting, 7 = fragment
// caught (R17: the boss itself is never caught, only a fragment of it).
#define NEXUS_PROGRESS_CHAMPION     NEXUS_TRAINER_ROOMS         // 4 won: champion pending
#define NEXUS_PROGRESS_BOSS         (NEXUS_TRAINER_ROOMS + 1)   // 5 won: legendary pending
#define NEXUS_PROGRESS_FRAGMENT     (NEXUS_TRAINER_ROOMS + 2)   // 6: legendary beaten, fragment waiting
#define NEXUS_PROGRESS_DONE         (NEXUS_TRAINER_ROOMS + 3)   // 7: fragment caught, day finished

// What Nexus_GetBossRoomState returns.
#define NEXUS_BOSS_ROOM_NONE        0   // not the boss room
#define NEXUS_BOSS_ROOM_LEGENDARY   1   // the legendary waits
#define NEXUS_BOSS_ROOM_DONE        2   // day finished (prize / gift may still wait)
#define NEXUS_BOSS_ROOM_FRAGMENT    3   // beaten: its fragment waits for a ball

// What Nexus_GetDoorState returns for one door of the current room.
#define NEXUS_DOOR_HIDDEN           0   // not in this room, or closed by another choice
#define NEXUS_DOOR_FIGHT            1   // its guardian is waiting (chosen or still choosable)
#define NEXUS_DOOR_PASS             2   // guardian beaten: the portal leads to the next room

// R10: Nexus_CheckTraditional result.
#define NEXUS_TRADITIONAL_OK            0
#define NEXUS_TRADITIONAL_LEGENDARY     1   // more than one legendary
#define NEXUS_TRADITIONAL_SUB           2   // more than one sub-legendary
#define NEXUS_TRADITIONAL_MEGA          3   // more than one Mega / Primal

// R10: the category of one party slot (Nexus_GetSlotCategory).
#define NEXUS_CATEGORY_COMMON       0
#define NEXUS_CATEGORY_SUB          1
#define NEXUS_CATEGORY_LEGENDARY    2

#endif // GUARD_CONSTANTS_NEXUS_H
