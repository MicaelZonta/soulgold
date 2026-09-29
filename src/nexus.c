// Nexus (Rift Missions post-game loop): the RULES.
//
// Rules document:  .claude/rift_missions/nexus/NEXUS_REGRAS.md (R1..R16)
// Implementation:  .claude/rift_missions/nexus/NEXUS_IMPLEMENTATION.md
//
// Split on purpose:
//   - CONTENT (who can appear, which legendary, which prizes) is only in the
//     tables of src/data/nexus/*.h. Adding a trainer or a legendary never
//     touches this file.
//   - RULES are the functions below, one block per rule of NEXUS_REGRAS.md.
//     Changing a rule changes only its block.
//   - The FLOW (rooms, doors, texts, choreography) is the map script,
//     data/maps/Nexus/scripts.inc, which only asks questions through the
//     specials at the end of this file.

#include "global.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "item.h"
#include "nexus.h"
#include "pokeball.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "string_util.h"
#include "battle_boss.h"
#include "constants/battle.h"
#include "constants/characters.h"
#include "constants/event_objects.h"
#include "constants/form_change_types.h"
#include "constants/items.h"
#include "constants/opponents.h"
#include "constants/pokeball.h"
#include "constants/species.h"

#include "data/nexus/trainers.h"
#include "data/nexus/legendaries.h"
#include "data/nexus/prizes.h"
#include "data/nexus/mythicals.h"

#define NEXUS_LEGENDARY_COUNT ARRAY_COUNT(gNexusLegendaries)
#define NEXUS_NO_TRAINER      0xFF

// A room needs three trainers besides the champion of the day AND besides
// the three of the room before it (GetRoomTrio excludes both).
STATIC_ASSERT(NEXUS_TRAINER_COUNT >= 2 * NEXUS_DOORS_PER_ROOM + 1, NexusNeedsMoreTrainersThanDoors);
STATIC_ASSERT(NEXUS_LEGENDARY_COUNT > 0, NexusNeedsALegendary);

// ===========================================================================
// R15. The day's state: one var. What the player DID is stored; what the
// game DREW is recomputed from the daily seed.
//
//   bits  0-7   door chosen in trainer rooms 1..4, 2 bits each (3 = none yet)
//   bits  8-10  progress: fights won 0..5, 6 = legendary beaten (fragment
//               waiting), 7 = fragment caught (R17)
//   bit   11    R9 prize taken today
//   bit   12    after-boss gift taken today (afterBossScript of the legendary)
//   bits 13-15  room the player is standing in, 0..5 (where a reload puts the player)
// ===========================================================================
#define STATE_DOOR_SHIFT(room)  ((room) * 2)
#define STATE_DOOR_MASK         0x3
#define STATE_PROGRESS_SHIFT    8
#define STATE_PROGRESS_MASK     0x7
#define STATE_PRIZE_BIT         (1 << 11)
#define STATE_GIFT_BIT          (1 << 12)
#define STATE_ROOM_SHIFT        13
#define STATE_ROOM_MASK         0x7

// Every door "not chosen", nothing won, room 0.
#define STATE_FRESH             0x00FF

STATIC_ASSERT(NEXUS_DOOR_NONE == STATE_DOOR_MASK, NexusDoorNoneIsTheEmptyField);
STATIC_ASSERT(NEXUS_PROGRESS_DONE <= STATE_PROGRESS_MASK, NexusProgressFitsItsField);
STATIC_ASSERT(NEXUS_ROOM_COUNT - 1 <= STATE_ROOM_MASK, NexusRoomFitsItsField);

static u32 GetStateField(u32 shift, u32 mask)
{
    return (VarGet(VAR_NEXUS_DAILY) >> shift) & mask;
}

static void SetStateField(u32 shift, u32 mask, u32 value)
{
    u16 state = VarGet(VAR_NEXUS_DAILY);

    state &= ~(mask << shift);
    state |= (value & mask) << shift;
    VarSet(VAR_NEXUS_DAILY, state);
}

static bool32 GetStateBit(u32 bit)
{
    return (VarGet(VAR_NEXUS_DAILY) & bit) != 0;
}

static void SetStateBit(u32 bit)
{
    VarSet(VAR_NEXUS_DAILY, VarGet(VAR_NEXUS_DAILY) | bit);
}

static u32 GetProgress(void)             { return GetStateField(STATE_PROGRESS_SHIFT, STATE_PROGRESS_MASK); }
static void SetProgress(u32 progress)    { SetStateField(STATE_PROGRESS_SHIFT, STATE_PROGRESS_MASK, progress); }
static u32 GetRoom(void)                 { return GetStateField(STATE_ROOM_SHIFT, STATE_ROOM_MASK); }
static void SetRoom(u32 room)            { SetStateField(STATE_ROOM_SHIFT, STATE_ROOM_MASK, room); }
static u32 GetChosenDoor(u32 room)       { return GetStateField(STATE_DOOR_SHIFT(room), STATE_DOOR_MASK); }
static void SetChosenDoor(u32 room, u32 door) { SetStateField(STATE_DOOR_SHIFT(room), STATE_DOOR_MASK, door); }

// R15, "zerar na virada do dia": the Kurt pattern. A var is not cleared by the
// date change; the DAILY flag is. Found clear -> a new day -> fresh state.
static void RollOverIfNewDay(void)
{
    if (!FlagGet(FLAG_DAILY_NEXUS_NEW_DAY))
    {
        VarSet(VAR_NEXUS_DAILY, STATE_FRESH);
        FlagSet(FLAG_DAILY_NEXUS_NEW_DAY);
    }
}

// ===========================================================================
// R3 / R15. The draw: same day -> same result, next day -> a new one, and
// nothing of it in the save. gSaveBlock1Ptr->dailySeed changes in
// UpdatePerDay (src/clock.c) together with ClearDailyFlags, so the draw and
// the state above turn over at the same moment. Its own mixing, so it never
// consumes the game's RNG.
// ===========================================================================
enum
{
    SALT_LEGENDARY = 1,
    SALT_ROOMS,
    SALT_PRIZE_GROUP,
    SALT_PRIZE_ITEM,
    SALT_BOSS_FORM,
};

static u32 DailyHash(u32 salt)
{
    u32 x = gSaveBlock1Ptr->dailySeed ^ (salt * 0x9E3779B9);

    x ^= x >> 16;
    x *= 0x45D9F3B;
    x ^= x >> 16;
    x *= 0x45D9F3B;
    x ^= x >> 16;
    return x;
}

// ===========================================================================
// R1. A legendary that can be obtained outside the Nexus is only drawn once
// the player has caught it. R7: no other filter (repeats are fine).
// ===========================================================================
static bool32 IsLegendaryEligible(const struct NexusLegendary *legendary)
{
    if (!legendary->requiresCaught)
        return TRUE;
    return GetSetPokedexFlag(SpeciesToNationalPokedexNum(legendary->species), FLAG_GET_CAUGHT);
}

// R5: the legendary of the day. If a capture outside the Nexus makes a new one
// eligible, the result may change within the day (accepted by R15).
static const struct NexusLegendary *GetTodaysLegendary(void)
{
    u8 eligible[NEXUS_LEGENDARY_COUNT];
    u32 i, count = 0;

    for (i = 0; i < NEXUS_LEGENDARY_COUNT; i++)
    {
        if (IsLegendaryEligible(&gNexusLegendaries[i]))
            eligible[count++] = i;
    }

    if (count == 0) // every legendary gated by R1: fall back to the first line
        return &gNexusLegendaries[0];
    return &gNexusLegendaries[eligible[DailyHash(SALT_LEGENDARY) % count]];
}

// ===========================================================================
// R5 / R5.1. The trainers behind the doors. Each room shuffles the pool
// minus the champion of the day and minus the trio of the room before it,
// then takes the first three. So a room never repeats a person, two rooms
// in a row never share one, and no room ever shows another room's exact
// trio again (the old "wrap" handed room 4 the same three people as room 1,
// which read as broken randomization). R7 still holds: with a pool this
// size a trainer can return in a later, non-adjacent room of the same day.
// ===========================================================================
static void GetRoomTrio(u32 targetRoom, u8 *trio)
{
    u8 prev[NEXUS_DOORS_PER_ROOM];
    u32 champion = GetTodaysLegendary()->champion;
    u32 room, i, d;

    for (d = 0; d < NEXUS_DOORS_PER_ROOM; d++)
        prev[d] = NEXUS_NO_TRAINER;

    for (room = 0; room <= targetRoom; room++)
    {
        u8 pool[NEXUS_TRAINER_COUNT];
        u32 count = 0;
        // Its own stream per room, all derived from the daily seed.
        u32 rng = DailyHash(SALT_ROOMS) ^ (room * 0x85EBCA6B);

        for (i = 0; i < NEXUS_TRAINER_COUNT; i++)
        {
            if (i == champion)
                continue;
            for (d = 0; d < NEXUS_DOORS_PER_ROOM; d++)
            {
                if (prev[d] == i)
                    break;
            }
            if (d == NEXUS_DOORS_PER_ROOM)
                pool[count++] = i;
        }

        // Fisher-Yates driven by an LCG
        for (i = count - 1; i > 0; i--)
        {
            u32 j;
            u8 tmp;

            rng = rng * 1103515245 + 12345;
            j = (rng >> 16) % (i + 1);
            tmp = pool[i];
            pool[i] = pool[j];
            pool[j] = tmp;
        }

        for (d = 0; d < NEXUS_DOORS_PER_ROOM; d++)
        {
            trio[d] = pool[d];
            prev[d] = pool[d];
        }
    }
}

static u32 GetRoomDoorTrainer(u32 room, u32 door)
{
    u8 trio[NEXUS_DOORS_PER_ROOM];

    if (room == NEXUS_ROOM_CHAMPION)
        return (door == NEXUS_DOOR_CHAMPION) ? GetTodaysLegendary()->champion : NEXUS_NO_TRAINER;
    if (room >= NEXUS_TRAINER_ROOMS || door >= NEXUS_DOORS_PER_ROOM)
        return NEXUS_NO_TRAINER;

    GetRoomTrio(room, trio);
    return trio[door];
}

// ===========================================================================
// R3 / R5.1. What a door of the current room is.
//   - Room being fought (room == progress): every door FIGHT until one is
//     chosen; then only the chosen one.
//   - Room already won (room < progress): only the chosen door, as PASS.
//     R3: "walks from the first room, but does not fight again".
// ===========================================================================
static u32 GetDoorState(u32 room, u32 door)
{
    u32 progress = GetProgress();
    u32 chosen;

    if (room > NEXUS_ROOM_CHAMPION || GetRoomDoorTrainer(room, door) == NEXUS_NO_TRAINER)
        return NEXUS_DOOR_HIDDEN;

    chosen = (room == NEXUS_ROOM_CHAMPION) ? NEXUS_DOOR_CHAMPION : GetChosenDoor(room);
    if (chosen == NEXUS_DOOR_NONE && progress > room)
        chosen = NEXUS_DOOR_NORTH; // never written like this; keeps the way open anyway
    if (chosen != NEXUS_DOOR_NONE && chosen != door)
        return NEXUS_DOOR_HIDDEN;

    if (progress > room)
        return NEXUS_DOOR_PASS;
    if (progress == room)
        return NEXUS_DOOR_FIGHT;
    return NEXUS_DOOR_HIDDEN;
}

// A reload never leaves the player ahead of the progress, and a beaten
// legendary always opens on the last room (its fragment, the prize and the
// gift wait there).
static void ClampRoom(void)
{
    u32 progress = GetProgress();

    if (progress >= NEXUS_PROGRESS_FRAGMENT)
        SetRoom(NEXUS_ROOM_BOSS);
    else if (GetRoom() > progress)
        SetRoom(progress);
}

// ===========================================================================
// R2 / R6 / R8. The boss: the legendary of the day at the highest level of
// the player's party (eggs excluded), with the boss parameters of its line in
// the table. 3 perfect IVs come from the species (perfectIVCount).
// ===========================================================================
// R19. A legendary with a superior form is ALWAYS fought in it: never plain
// Mewtwo, always Mega Mewtwo X or Y - which one is drawn for the day. Superior
// = Mega Evolution (stone or move), Primal Reversion, Ultra Burst, and the
// fusions of the species that fuses (Kyurem -> Black/White, Necrozma -> Dusk
// Mane/Dawn Wings, Calyrex -> Ice/Shadow; the partners get nothing). Followed
// up to two steps: Necrozma -> Dusk Mane or Dawn Wings -> Ultra Necrozma.
static bool32 IsSuperiorFormChange(u16 method)
{
    switch (method)
    {
    case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
    case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE:
    case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
    case FORM_CHANGE_BATTLE_ULTRA_BURST:
        return TRUE;
    }
    return FALSE;
}

static u16 GetBossSpecies(void)
{
    u16 species = GetTodaysLegendary()->species;
    u32 step, i;

    for (step = 0; step < 2; step++)
    {
        const struct FormChange *formChanges = GetSpeciesFormChanges(species);
        const struct Fusion *fusions = gFusionTablePointers[species];
        u16 forms[8];
        u32 count = 0;

        for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR && count < ARRAY_COUNT(forms); i++)
        {
            if (IsSuperiorFormChange(formChanges[i].method) && formChanges[i].targetSpecies != species)
                forms[count++] = formChanges[i].targetSpecies;
        }
        for (i = 0; fusions != NULL && fusions[i].fusionStorageIndex != FUSION_TERMINATOR && count < ARRAY_COUNT(forms); i++)
        {
            if (fusions[i].targetSpecies1 == species)
                forms[count++] = fusions[i].fusingIntoMon;
        }
        if (count == 0)
            break;
        species = forms[DailyHash(SALT_BOSS_FORM + step) % count];
    }
    return species;
}

static u32 GetBossLevel(void)
{
    s32 level = GetHighestLevelInPlayerParty();

    if (level < 1)
        level = 1;
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;
    return level;
}

// ===========================================================================
// R17. The fragment. The Nexus is a broken reality, loose in time and space:
// what is fought there is a concept, and a concept cannot be caught. Beating
// the boss leaves a fragment of it - the FIRST FORM of the species (Silvally
// -> Type: Null, Naganadel -> Poipole, any battle form -> its base form), at
// LEVEL 1, with at least the boss's perfect IVs (R8). An Ultra Beast's
// fragment only goes into a Beast Ball; anything else, into any ball the
// player picks from the Bag.
// ===========================================================================
static u16 GetFragmentSpecies(u16 species)
{
    u32 i;

    species = GET_BASE_SPECIES_ID(species);
    for (i = 0; i < 3; i++) // a line has at most three stages
    {
        u16 pre = GetSpeciesPreEvolution(species);

        if (pre == SPECIES_NONE)
            break;
        species = GET_BASE_SPECIES_ID(pre);
    }
    return species;
}

// Necrozma is not isUltraBeast in the engine, but here it came out of Ultra
// Space like one (author, 28/09/2026): Beast Ball only, every form. Only this
// rule - it stays a legendary in the pool.
static bool32 FragmentNeedsBeastBall(u16 bossSpecies)
{
    bossSpecies = SanitizeSpeciesId(bossSpecies);
    return gSpeciesInfo[bossSpecies].isUltraBeast
        || GET_BASE_SPECIES_ID(bossSpecies) == SPECIES_NECROZMA;
}

// R8 carried over: a first form may have fewer guaranteed perfect IVs than
// the boss (Poipole vs Naganadel). Raise random stats to 31 until it matches.
static void GiveFragmentBossPerfectIVs(struct Pokemon *mon, u16 bossSpecies)
{
    u32 wanted = gSpeciesInfo[SanitizeSpeciesId(bossSpecies)].perfectIVCount;
    u32 i, perfect = 0;
    u8 max = MAX_PER_STAT_IVS;

    for (i = 0; i < NUM_STATS; i++)
    {
        if (GetMonData(mon, MON_DATA_HP_IV + i) == MAX_PER_STAT_IVS)
            perfect++;
    }
    while (perfect < wanted && perfect < NUM_STATS)
    {
        i = Random() % NUM_STATS;
        if (GetMonData(mon, MON_DATA_HP_IV + i) != MAX_PER_STAT_IVS)
        {
            SetMonData(mon, MON_DATA_HP_IV + i, &max);
            perfect++;
        }
    }
    CalculateMonStats(mon);
}

// ===========================================================================
// R9. The prize of the day: a weighted group, then one item of it.
// ===========================================================================
static u16 GetTodaysPrize(void)
{
    u32 i, total = 0, roll;

    for (i = 0; i < ARRAY_COUNT(sNexusPrizeGroups); i++)
        total += sNexusPrizeGroups[i].weight;

    roll = DailyHash(SALT_PRIZE_GROUP) % total;
    for (i = 0; i < ARRAY_COUNT(sNexusPrizeGroups) - 1; i++)
    {
        if (roll < sNexusPrizeGroups[i].weight)
            break;
        roll -= sNexusPrizeGroups[i].weight;
    }

    return sNexusPrizeGroups[i].firstItem + DailyHash(SALT_PRIZE_ITEM) % sNexusPrizeGroups[i].count;
}

// ===========================================================================
// R10. Traditional format: at most 1 legendary, 1 sub-legendary, 1 Mega.
// ===========================================================================
static u32 Nexus_GetSpeciesCategory(u16 species)
{
    const struct SpeciesInfo *info = &gSpeciesInfo[SanitizeSpeciesId(species)];
    u32 i;

    if (info->isRestrictedLegendary)
        return NEXUS_CATEGORY_LEGENDARY;
    if (info->isMythical)
    {
        u16 base = GET_BASE_SPECIES_ID(species);

        for (i = 0; i < ARRAY_COUNT(sNexusLegendaryMythicals); i++)
        {
            if (sNexusLegendaryMythicals[i] == base)
                return NEXUS_CATEGORY_LEGENDARY;
        }
        return NEXUS_CATEGORY_SUB;
    }
    if (info->isSubLegendary || info->isUltraBeast || info->isParadox)
        return NEXUS_CATEGORY_SUB;
    return NEXUS_CATEGORY_COMMON;
}

static bool32 MonHoldsItem(struct Pokemon *mon, u16 item)
{
    u32 i;

    for (i = 0; i < MAX_MON_ITEMS; i++)
    {
        if (GetMonData(mon, MON_DATA_HELD_ITEM + i) == item)
            return TRUE;
    }
    return FALSE;
}

static bool32 MonKnowsMove(struct Pokemon *mon, u16 move)
{
    u32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMonData(mon, MON_DATA_MOVE1 + i) == move)
            return TRUE;
    }
    return FALSE;
}

// Mega = holds its own Mega Stone (or Rayquaza with Dragon Ascent); a Primal
// orb takes the Mega slot too. The Mega of a legendary takes both slots,
// which falls out of counting the two separately.
static bool32 IsMonMega(struct Pokemon *mon)
{
    const struct FormChange *formChanges = GetSpeciesFormChanges(GetMonData(mon, MON_DATA_SPECIES));
    u32 i;

    if (formChanges == NULL)
        return FALSE;

    for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        switch (formChanges[i].method)
        {
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM:
        case FORM_CHANGE_BATTLE_PRIMAL_REVERSION:
            if (MonHoldsItem(mon, formChanges[i].param1))
                return TRUE;
            break;
        case FORM_CHANGE_BATTLE_MEGA_EVOLUTION_MOVE:
            if (MonKnowsMove(mon, formChanges[i].param1))
                return TRUE;
            break;
        default:
            break;
        }
    }
    return FALSE;
}

static u32 CheckPartyTraditional(void)
{
    u32 i, legendaries = 0, subs = 0, megas = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u16 species = GetMonData(mon, MON_DATA_SPECIES);

        if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
            continue;

        switch (Nexus_GetSpeciesCategory(species))
        {
        case NEXUS_CATEGORY_LEGENDARY:
            legendaries++;
            break;
        case NEXUS_CATEGORY_SUB:
            subs++;
            break;
        }
        if (IsMonMega(mon))
            megas++;
    }

    if (legendaries > 1)
        return NEXUS_TRADITIONAL_LEGENDARY;
    if (subs > 1)
        return NEXUS_TRADITIONAL_SUB;
    if (megas > 1)
        return NEXUS_TRADITIONAL_MEGA;
    return NEXUS_TRADITIONAL_OK;
}

// ===========================================================================
// R2 for trainers: src/level_scaling.c asks this, so the scaling list is the
// trainer table itself.
// ===========================================================================
bool32 Nexus_IsNexusTrainer(u16 trainerId)
{
    u32 i;

    for (i = 0; i < NEXUS_TRAINER_COUNT; i++)
    {
        if (gNexusTrainers[i].trainerId == trainerId)
            return TRUE;
    }
    return FALSE;
}

// ===========================================================================
// Script interface (data/specials.inc). Door arguments come in VAR_0x8004.
// ===========================================================================

// Sun and Moon Altar rift, right before the warp: a new run starts in room 1
// (R3), a finished day in the last room.
void Nexus_EnterFromAltar(void)
{
    RollOverIfNewDay();
    SetRoom(0);
    ClampRoom();
}

// VAR_OBJ_GFX_ID_3: the legendary while it stands, its fragment (R17) once
// it was beaten - the same object at (10,6) shows one or the other.
// The boss's superior form (R19) is shown only if it has an overworld
// sprite of its own (Megas usually do not); otherwise its base form.
static void SetLegendaryObjectGfx(void)
{
    u16 species = GetBossSpecies();

    if (GetProgress() >= NEXUS_PROGRESS_FRAGMENT)
        species = GetFragmentSpecies(species);
    else if (gSpeciesInfo[species].overworldData.tileTag == 0)
        species = GET_BASE_SPECIES_ID(species);
    VarSet(VAR_OBJ_GFX_ID_3, OBJ_EVENT_MON + species);
}

// Map ON_TRANSITION: new day check, safe room, and the sprites of this room:
// VAR_OBJ_GFX_ID_0..2 = the trainers of the west/north/east doors,
// VAR_OBJ_GFX_ID_3 = the legendary.
void Nexus_BeginMapLoad(void)
{
    u32 door, room;

    RollOverIfNewDay();
    ClampRoom();
    room = GetRoom();

    for (door = 0; door < NEXUS_DOORS_PER_ROOM; door++)
    {
        u32 trainer = GetRoomDoorTrainer(room, door);
        u16 gfx = (trainer == NEXUS_NO_TRAINER) ? OBJ_EVENT_GFX_BOY_1 : gNexusTrainers[trainer].graphicsId;

        VarSet(VAR_OBJ_GFX_ID_0 + door, gfx);
    }
    SetLegendaryObjectGfx();
}

u16 Nexus_GetRoom(void)
{
    return GetRoom();
}

u16 Nexus_GetProgress(void)
{
    return GetProgress();
}

u16 Nexus_GetDoorState(void)
{
    return GetDoorState(GetRoom(), gSpecialVar_0x8004);
}

// STR_VAR_1 = the name of the trainer behind door VAR_0x8004.
void Nexus_BufferDoorTrainerName(void)
{
    u32 trainer = GetRoomDoorTrainer(GetRoom(), gSpecialVar_0x8004);

    if (trainer == NEXUS_NO_TRAINER)
        gStringVar1[0] = EOS;
    else
        StringCopy(gStringVar1, GetTrainerNameFromId(gNexusTrainers[trainer].trainerId));
}

// A door of the current trainer room was already chosen (on this or an
// earlier attempt today): the other portals are already closed.
u16 Nexus_IsRoomChosen(void)
{
    u32 room = GetRoom();

    return room < NEXUS_TRAINER_ROOMS && GetChosenDoor(room) != NEXUS_DOOR_NONE;
}

// R5.1 / R15: written the moment the player commits, never at the end.
void Nexus_ChooseDoor(void)
{
    u32 room = GetRoom();

    if (room < NEXUS_TRAINER_ROOMS && GetChosenDoor(room) == NEXUS_DOOR_NONE)
        SetChosenDoor(room, gSpecialVar_0x8004);
}

// callnative: runs the fight of door VAR_0x8004 (data/scripts/nexus.inc). The
// champion room runs the lines about the legendary (R16). The fight leaves
// its B_OUTCOME_* in VAR_TEMP_3 and returns here.
void Nexus_CallDoorFight(struct ScriptContext *ctx)
{
    u32 room = GetRoom();
    u32 trainer = GetRoomDoorTrainer(room, gSpecialVar_0x8004);

    if (trainer == NEXUS_NO_TRAINER)
        return;
    if (room == NEXUS_ROOM_CHAMPION)
        ScriptCall(ctx, GetTodaysLegendary()->championScript);
    else
        ScriptCall(ctx, gNexusTrainers[trainer].fightScript);
}

// R15: progress is written right after the victory.
void Nexus_RecordFightWon(void)
{
    u32 room = GetRoom();

    if (GetProgress() == room && room <= NEXUS_ROOM_CHAMPION)
        SetProgress(room + 1);
}

void Nexus_AdvanceRoom(void)
{
    u32 room = GetRoom();

    if (room < NEXUS_ROOM_BOSS && GetProgress() > room)
        SetRoom(room + 1);
}

// Walking out by the south: the next entry starts in room 1 again (R3).
void Nexus_LeaveToAltar(void)
{
    SetRoom(0);
}

// The boss room: NEXUS_BOSS_ROOM_*.
u16 Nexus_GetBossRoomState(void)
{
    if (GetRoom() != NEXUS_ROOM_BOSS)
        return NEXUS_BOSS_ROOM_NONE;
    switch (GetProgress())
    {
    case NEXUS_PROGRESS_BOSS:
        return NEXUS_BOSS_ROOM_LEGENDARY;
    case NEXUS_PROGRESS_FRAGMENT:
        return NEXUS_BOSS_ROOM_FRAGMENT;
    case NEXUS_PROGRESS_DONE:
        return NEXUS_BOSS_ROOM_DONE;
    }
    return NEXUS_BOSS_ROOM_NONE;
}

// Right before BattleSetup_StartLegendaryEncounter:
// VAR_0x8004 species, VAR_0x8005 level, boss configured.
void Nexus_SetupBoss(void)
{
    const struct NexusLegendary *legendary = GetTodaysLegendary();

    gSpecialVar_0x8004 = GetBossSpecies();
    gSpecialVar_0x8005 = GetBossLevel();
    ConfigureBossBattleWithProfile(legendary->bossBars, SPECIES_NONE, legendary->bossStatMultiplier, legendary->bossPhaseProfile);
}

// R17 / R15: the boss was knocked out - written right after the battle. The
// fragment now waits at (10,6) until the player has a ball (and room) for it.
void Nexus_RecordBossBeaten(void)
{
    if (GetProgress() == NEXUS_PROGRESS_BOSS)
        SetProgress(NEXUS_PROGRESS_FRAGMENT);
    SetLegendaryObjectGfx();
}

void Nexus_RecordCapture(void)
{
    if (GetProgress() == NEXUS_PROGRESS_FRAGMENT)
        SetProgress(NEXUS_PROGRESS_DONE);
}

// STR_VAR_1 = the fragment's species, STR_VAR_2 = the legendary it came from.
void Nexus_BufferFragmentNames(void)
{
    u16 species = GetTodaysLegendary()->species;

    StringCopy(gStringVar1, GetSpeciesName(GetFragmentSpecies(species)));
    StringCopy(gStringVar2, GetSpeciesName(species));
}

// R17: TRUE when only a Beast Ball can hold today's fragment.
u16 Nexus_FragmentNeedsBeastBall(void)
{
    return FragmentNeedsBeastBall(GetTodaysLegendary()->species);
}

u16 Nexus_HasAnyBall(void)
{
    return IsBagPocketNonEmpty(POCKET_POKE_BALLS);
}

// R17: the fragment goes into the ball item in VAR_0x8005 (the script checked
// party AND box space before offering, and removes the ball only on success).
// VAR_RESULT = MON_GIVEN_TO_PARTY / MON_GIVEN_TO_PC / MON_CANT_GIVE;
// VAR_0x8004 = the fragment's species, for bufferspeciesname.
// R17 exception (author, 28/09/2026): a Deoxys fragment comes in a random
// Forme. It is the only source of Attack/Defense/Speed - the Meteorite lives in
// Mt. Chimney, outside the ROM (.claude/evolucoes.md).
static const u16 sDeoxysFragmentForms[] =
{
    SPECIES_DEOXYS_NORMAL,
    SPECIES_DEOXYS_ATTACK,
    SPECIES_DEOXYS_DEFENSE,
    SPECIES_DEOXYS_SPEED,
};

void Nexus_GiveFragment(void)
{
    u16 bossSpecies = GetTodaysLegendary()->species;
    u16 species = GetFragmentSpecies(bossSpecies);
    struct Pokemon mon;
    u8 ball = ItemIdToBallId(gSpecialVar_0x8005);

    if (species == SPECIES_DEOXYS_NORMAL)
        species = sDeoxysFragmentForms[Random() % ARRAY_COUNT(sDeoxysFragmentForms)];
    CreateRandomMon(&mon, species, 1);
    GiveFragmentBossPerfectIVs(&mon, bossSpecies);
    SetMonData(&mon, MON_DATA_POKEBALL, &ball);
    gSpecialVar_0x8004 = species;
    gSpecialVar_Result = GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
}

// callnative: the optional script of the legendary of the day (Poipole).
void Nexus_CallAfterBossScript(struct ScriptContext *ctx)
{
    const struct NexusLegendary *legendary = GetTodaysLegendary();

    if (legendary->afterBossScript != NULL)
        ScriptCall(ctx, legendary->afterBossScript);
}

// R18: the Looker File notebook lies in the champion room when today's
// legendary has one.
u16 Nexus_HasLookerFile(void)
{
    return GetRoom() == NEXUS_ROOM_CHAMPION && GetTodaysLegendary()->lookerFileScript != NULL;
}

// callnative: the page of today's Looker File (data/scripts/nexus.inc).
void Nexus_CallLookerFileScript(struct ScriptContext *ctx)
{
    const struct NexusLegendary *legendary = GetTodaysLegendary();

    if (legendary->lookerFileScript != NULL)
        ScriptCall(ctx, legendary->lookerFileScript);
}

u16 Nexus_IsGiftTaken(void)
{
    return GetStateBit(STATE_GIFT_BIT);
}

void Nexus_MarkGiftTaken(void)
{
    SetStateBit(STATE_GIFT_BIT);
}

// VAR_RESULT = today's prize (R9), or ITEM_NONE if not earned or already taken.
u16 Nexus_GetPrize(void)
{
    if (GetProgress() < NEXUS_PROGRESS_DONE || GetStateBit(STATE_PRIZE_BIT))
        return ITEM_NONE;
    return GetTodaysPrize();
}

void Nexus_MarkPrizeTaken(void)
{
    SetStateBit(STATE_PRIZE_BIT);
}

u16 Nexus_CheckTraditional(void)
{
    return CheckPartyTraditional();
}

// Fragment caught today (for the altar's lines). A state left from another
// day does not count.
u16 Nexus_IsDoneToday(void)
{
    return FlagGet(FLAG_DAILY_NEXUS_NEW_DAY) && GetProgress() >= NEXUS_PROGRESS_DONE;
}

// Debug menu (Rift Missions > Nexus: new day): what the date change does to
// the Nexus - fresh state on the next touch and a new daily seed.
void Nexus_DebugNewDay(void)
{
    FlagClear(FLAG_DAILY_NEXUS_NEW_DAY);
    gSaveBlock1Ptr->dailySeed = Random32();
}
