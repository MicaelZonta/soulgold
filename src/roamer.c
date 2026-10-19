#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "ow_synchronize.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_objects.h"

// Despite having a variable to track it, the roamer is
// hard-coded to only ever be in map group 0
#define ROAMER_MAP_GROUP 0

enum
{
    MAP_GRP, // map group
    MAP_NUM, // map number
};

#define ROAMER(index) (&gSaveBlock1Ptr->roamer[index])
EWRAM_DATA static u8 sLocationHistory[ROAMER_COUNT][3][2] = {0};
EWRAM_DATA static u8 sRoamerLocation[ROAMER_COUNT][2] = {0};
EWRAM_DATA u8 gEncounteredRoamerIndex = 0;

#define ___ MAP_NUM(MAP_UNDEFINED) // For empty spots in the location table

// Note: There are two potential softlocks that can occur with this table if its maps are
//       changed in particular ways. They can be avoided by ensuring the following:
//       - There must be at least 2 location sets that start with a different map,
//         i.e. every location set cannot start with the same map. This is because of
//         the while loop in RoamerMoveToOtherLocationSet.
//       - Each location set must have at least 3 unique maps. This is because of
//         the while loop in RoamerMove. In this loop the first map in the set is
//         ignored, and an additional map is ignored if the roamer was there recently.
//       - Additionally, while not a softlock, it's worth noting that if for any
//         map in the location table there is not a location set that starts with
//         that map then the roamer will be significantly less likely to move away
//         from that map when it lands there.
enum
{
    ROAMER_LOC_TABLE_JOHTO,
    ROAMER_LOC_TABLE_KANTO,
    ROAMER_LOC_TABLE_COUNT,
};

static const u8 sRoamerLocationsJohto[][6] =
{
    { MAP_NUM(MAP_ROUTE29), MAP_NUM(MAP_ROUTE30), MAP_NUM(MAP_ROUTE46), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE30), MAP_NUM(MAP_ROUTE29), MAP_NUM(MAP_ROUTE31), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE31), MAP_NUM(MAP_ROUTE30), MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE36), ___, ___ },
    { MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE36), MAP_NUM(MAP_ROUTE31), MAP_NUM(MAP_ROUTE33), ___, ___ },
    { MAP_NUM(MAP_ROUTE33), MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE34), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE34), MAP_NUM(MAP_ROUTE33), MAP_NUM(MAP_ROUTE35), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE35), MAP_NUM(MAP_ROUTE34), MAP_NUM(MAP_ROUTE36), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE36), MAP_NUM(MAP_ROUTE35), MAP_NUM(MAP_ROUTE31), MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE37), ___ },
    { MAP_NUM(MAP_ROUTE37), MAP_NUM(MAP_ROUTE36), MAP_NUM(MAP_ROUTE38), MAP_NUM(MAP_ROUTE42), ___, ___ },
    { MAP_NUM(MAP_ROUTE38), MAP_NUM(MAP_ROUTE37), MAP_NUM(MAP_ROUTE39), MAP_NUM(MAP_ROUTE42), ___, ___ },
    { MAP_NUM(MAP_ROUTE39), MAP_NUM(MAP_ROUTE38), MAP_NUM(MAP_ROUTE42), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE43), MAP_NUM(MAP_ROUTE42), MAP_NUM(MAP_ROUTE44), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE42), MAP_NUM(MAP_ROUTE43), MAP_NUM(MAP_ROUTE44), MAP_NUM(MAP_ROUTE37), MAP_NUM(MAP_ROUTE38), ___ },
    { MAP_NUM(MAP_ROUTE44), MAP_NUM(MAP_ROUTE42), MAP_NUM(MAP_ROUTE43), MAP_NUM(MAP_ROUTE45), ___, ___ },
    { MAP_NUM(MAP_ROUTE45), MAP_NUM(MAP_ROUTE44), MAP_NUM(MAP_ROUTE46), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE46), MAP_NUM(MAP_ROUTE45), MAP_NUM(MAP_ROUTE29), ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

static const u8 sRoamerLocationsKanto[][6] =
{
    { MAP_NUM(MAP_ROUTE1),  MAP_NUM(MAP_ROUTE2),  MAP_NUM(MAP_ROUTE22), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE2),  MAP_NUM(MAP_ROUTE1),  MAP_NUM(MAP_ROUTE3),  ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE3),  MAP_NUM(MAP_ROUTE2),  MAP_NUM(MAP_ROUTE4),  ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE4),  MAP_NUM(MAP_ROUTE3),  MAP_NUM(MAP_ROUTE5),  MAP_NUM(MAP_ROUTE24), ___, ___ },
    { MAP_NUM(MAP_ROUTE5),  MAP_NUM(MAP_ROUTE4),  MAP_NUM(MAP_ROUTE6),  MAP_NUM(MAP_ROUTE9),  ___, ___ },
    { MAP_NUM(MAP_ROUTE6),  MAP_NUM(MAP_ROUTE5),  MAP_NUM(MAP_ROUTE7),  MAP_NUM(MAP_ROUTE11), ___, ___ },
    { MAP_NUM(MAP_ROUTE7),  MAP_NUM(MAP_ROUTE6),  MAP_NUM(MAP_ROUTE8),  MAP_NUM(MAP_ROUTE16), ___, ___ },
    { MAP_NUM(MAP_ROUTE8),  MAP_NUM(MAP_ROUTE7),  MAP_NUM(MAP_ROUTE9),  MAP_NUM(MAP_ROUTE10), ___, ___ },
    { MAP_NUM(MAP_ROUTE9),  MAP_NUM(MAP_ROUTE5),  MAP_NUM(MAP_ROUTE8),  MAP_NUM(MAP_ROUTE10), ___, ___ },
    { MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE8),  MAP_NUM(MAP_ROUTE9),  ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE11), MAP_NUM(MAP_ROUTE6),  MAP_NUM(MAP_ROUTE12), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE12), MAP_NUM(MAP_ROUTE11), MAP_NUM(MAP_ROUTE13), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE13), MAP_NUM(MAP_ROUTE12), MAP_NUM(MAP_ROUTE14), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE14), MAP_NUM(MAP_ROUTE13), MAP_NUM(MAP_ROUTE15), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE14), MAP_NUM(MAP_ROUTE18), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE16), MAP_NUM(MAP_ROUTE7),  MAP_NUM(MAP_ROUTE17), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE17), MAP_NUM(MAP_ROUTE16), MAP_NUM(MAP_ROUTE18), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE17), MAP_NUM(MAP_ROUTE15), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE20), MAP_NUM(MAP_ROUTE21), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE20), MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE21), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE21), MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE20), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE22), MAP_NUM(MAP_ROUTE1),  MAP_NUM(MAP_ROUTE23), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE23), MAP_NUM(MAP_ROUTE22), MAP_NUM(MAP_ROUTE1),  ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE24), MAP_NUM(MAP_ROUTE4),  MAP_NUM(MAP_ROUTE25), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE25), MAP_NUM(MAP_ROUTE24), MAP_NUM(MAP_ROUTE4),  ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

struct RoamerLocationTable
{
    const u8 (*locations)[6];
    u8 numSets;
};

static const struct RoamerLocationTable sRoamerLocationTables[ROAMER_LOC_TABLE_COUNT] =
{
    [ROAMER_LOC_TABLE_JOHTO] = { sRoamerLocationsJohto, ARRAY_COUNT(sRoamerLocationsJohto) - 1 },
    [ROAMER_LOC_TABLE_KANTO] = { sRoamerLocationsKanto, ARRAY_COUNT(sRoamerLocationsKanto) - 1 },
};

#undef ___
#define NUM_LOCATIONS_PER_SET 6

static inline const u8 (*GetRoamerLocations(u32 roamerIndex))[6]
{
    return sRoamerLocationTables[ROAMER(roamerIndex)->locationTableId].locations;
}

static inline u8 GetRoamerNumLocationSets(u32 roamerIndex)
{
    return sRoamerLocationTables[ROAMER(roamerIndex)->locationTableId].numSets;
}

static bool8 IsMapInRoamerTable(u32 roamerIndex, u8 mapNum)
{
    const u8 (*locs)[6] = GetRoamerLocations(roamerIndex);
    u8 numSets = GetRoamerNumLocationSets(roamerIndex);
    u32 i;

    for (i = 0; i < numSets; i++)
    {
        if (locs[i][0] == mapNum)
            return TRUE;
    }
    return FALSE;
}

static u8 CountLegendariesInParty(void)
{
    u8 count = 0;
    u32 i;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        if (species != SPECIES_NONE
            && (gSpeciesInfo[species].isRestrictedLegendary
                || gSpeciesInfo[species].isSubLegendary
                || gSpeciesInfo[species].isMythical))
            count++;
    }
    return count;
}

// 2% por lendario na party (max 12% com 6): puxa o roamer para o mapa do jogador
static void TryAttractRoamer(u32 roamerIndex)
{
    u8 playerMapNum = gSaveBlock1Ptr->location.mapNum;
    u8 legendCount = CountLegendariesInParty();

    if (legendCount == 0)
        return;

    if (!IsMapInRoamerTable(roamerIndex, playerMapNum))
        return;

    if ((Random() % 100) < (legendCount * 2))
        sRoamerLocation[roamerIndex][MAP_NUM] = playerMapNum;
}

static void DeactivateRoamersByLocationTable(u8 locationTableId)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (ROAMER(i)->active && ROAMER(i)->locationTableId == locationTableId)
            SetRoamerInactive(i);
    }
}

void DeactivateAllRoamers(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
        SetRoamerInactive(i);
}

static void ClearRoamerLocationHistory(u32 roamerIndex)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sLocationHistory[roamerIndex]); i++)
    {
        sLocationHistory[roamerIndex][i][MAP_GRP] = 0;
        sLocationHistory[roamerIndex][i][MAP_NUM] = 0;
    }
}

void MoveAllRoamersToOtherLocationSets(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
        RoamerMoveToOtherLocationSet(i);
}

void MoveAllRoamers(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        RoamerMove(i);
        if (ROAMER(i)->active)
            TryAttractRoamer(i);
    }
}

static void CreateInitialRoamerMon(u8 index, u16 species, u8 level, u8 locationTableId)
{
    ClearRoamerLocationHistory(index);
    ROAMER(index)->locationTableId = locationTableId;
    u32 personality = GetMonPersonality(species,
        GetSynchronizedGender(ROAMER_ORIGIN, species),
        GetSynchronizedNature(ROAMER_ORIGIN, species),
        RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gEnemyParty[0], species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gEnemyParty[0]);
    ROAMER(index)->ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS);
    ROAMER(index)->personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY);
    ROAMER(index)->species = species;
    ROAMER(index)->level = level;
    ROAMER(index)->statusA = 0;
    ROAMER(index)->statusB = 0;
    ROAMER(index)->hp = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP);
    ROAMER(index)->cool = GetMonData(&gEnemyParty[0], MON_DATA_COOL);
    ROAMER(index)->beauty = GetMonData(&gEnemyParty[0], MON_DATA_BEAUTY);
    ROAMER(index)->cute = GetMonData(&gEnemyParty[0], MON_DATA_CUTE);
    ROAMER(index)->smart = GetMonData(&gEnemyParty[0], MON_DATA_SMART);
    ROAMER(index)->tough = GetMonData(&gEnemyParty[0], MON_DATA_TOUGH);
    ROAMER(index)->shiny = GetMonData(&gEnemyParty[0], MON_DATA_IS_SHINY);
    ROAMER(index)->active = TRUE;
    sRoamerLocation[index][MAP_GRP] = ROAMER_MAP_GROUP;
    sRoamerLocation[index][MAP_NUM] = GetRoamerLocations(index)[Random() % GetRoamerNumLocationSets(index)][0];
}

static u8 GetFirstInactiveRoamerIndex(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (!ROAMER(i)->active)
            return i;
    }
    return ROAMER_COUNT;
}

bool8 TryAddRoamer(u16 species, u8 level, u8 locationTableId)
{
    u8 index = GetFirstInactiveRoamerIndex();

    if (index < ROAMER_COUNT)
    {
        // Create the roamer and stop searching
        CreateInitialRoamerMon(index, species, level, locationTableId);
        return TRUE;
    }

    // Maximum active roamers found: do nothing and let the calling function know
    return FALSE;
}

bool8 HasActiveRoamers(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (ROAMER(i)->active)
            return TRUE;
    }

    return FALSE;
}

static const u16 sLegendaryBeastSpecies[] =
{
    SPECIES_ENTEI,
    SPECIES_RAIKOU,
    SPECIES_SUICUNE,
};

static bool8 IsRoamerSpeciesActive(u16 species)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (ROAMER(i)->active && ROAMER(i)->locationTableId == ROAMER_LOC_TABLE_JOHTO && ROAMER(i)->species == species)
            return TRUE;
    }

    return FALSE;
}

void InitRoamer(void)
{
    bool8 found[ARRAY_COUNT(sLegendaryBeastSpecies)] = {FALSE};
    u32 i;
    u32 j;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (!ROAMER(i)->active || ROAMER(i)->locationTableId != ROAMER_LOC_TABLE_JOHTO)
            continue;

        for (j = 0; j < ARRAY_COUNT(sLegendaryBeastSpecies); j++)
        {
            if (ROAMER(i)->species == sLegendaryBeastSpecies[j])
            {
                if (found[j])
                    SetRoamerInactive(i);
                else
                    found[j] = TRUE;
                break;
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(sLegendaryBeastSpecies); i++)
    {
        if (!IsRoamerSpeciesActive(sLegendaryBeastSpecies[i]))
            TryAddRoamer(sLegendaryBeastSpecies[i], 40, ROAMER_LOC_TABLE_JOHTO);
    }
}

// Porte fiel do InitKantoRoamers do HnS (la cria Latias/Latios Lv60 na tabela
// Kanto conforme gSpecialVar_0x8004). DECISAO DO AUTOR (Parte D): os latis
// existem so no LatiTemple; roamer/ilha dos latis NAO entram. A funcao e mantida
// apenas porque o script do Steven em Vermilion (importado) ainda faz
// "special InitKantoRoamers" e nao pode quebrar. Ela so desativa roamers da
// tabela Kanto e NAO cria nenhum roamer. O Steven sera re-roteirizado na Fase 7;
// quando isso acontecer, esta funcao pode ser removida (e o special tambem).
// Para um roamer de Kanto no futuro: TryAddRoamer(especie, nivel, ROAMER_LOC_TABLE_KANTO).
void InitKantoRoamers(void)
{
    DeactivateRoamersByLocationTable(ROAMER_LOC_TABLE_KANTO);
}

void UpdateLocationHistoryForRoamer(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        sLocationHistory[i][2][MAP_GRP] = sLocationHistory[i][1][MAP_GRP];
        sLocationHistory[i][2][MAP_NUM] = sLocationHistory[i][1][MAP_NUM];

        sLocationHistory[i][1][MAP_GRP] = sLocationHistory[i][0][MAP_GRP];
        sLocationHistory[i][1][MAP_NUM] = sLocationHistory[i][0][MAP_NUM];

        sLocationHistory[i][0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
        sLocationHistory[i][0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
    }
}

void RoamerMoveToOtherLocationSet(u32 roamerIndex)
{
    u8 mapNum = 0;

    if (!ROAMER(roamerIndex)->active)
        return;

    const u8 (*locs)[6] = GetRoamerLocations(roamerIndex);
    u8 numSets = GetRoamerNumLocationSets(roamerIndex);

    sRoamerLocation[roamerIndex][MAP_GRP] = ROAMER_MAP_GROUP;

    // Choose a location set that starts with a map
    // different from the roamer's current map
    do
    {
        mapNum = locs[Random() % numSets][0];
        if (sRoamerLocation[roamerIndex][MAP_NUM] != mapNum)
        {
            sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
            return;
        }
    } while (sRoamerLocation[roamerIndex][MAP_NUM] == mapNum);
    sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
}

void RoamerMove(u32 roamerIndex)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet(roamerIndex);
    }
    else
    {
        if (!ROAMER(roamerIndex)->active)
            return;

        const u8 (*locs)[6] = GetRoamerLocations(roamerIndex);
        u8 numSets = GetRoamerNumLocationSets(roamerIndex);

        while (locSet < numSets)
        {
            // Find the location set that starts with the roamer's current map
            if (sRoamerLocation[roamerIndex][MAP_NUM] == locs[locSet][0])
            {
                u8 mapNum;
                // Choose a new map (excluding the first) within this set
                // Also exclude a map if the roamer was there 2 moves ago
                do
                {
                    mapNum = locs[locSet][(Random() % (NUM_LOCATIONS_PER_SET - 1)) + 1];
                } while ((sLocationHistory[roamerIndex][2][MAP_GRP] == ROAMER_MAP_GROUP
                        && sLocationHistory[roamerIndex][2][MAP_NUM] == mapNum)
                        || mapNum == MAP_NUM(MAP_UNDEFINED));
                sRoamerLocation[roamerIndex][MAP_NUM] = mapNum;
                return;
            }
            locSet++;
        }
    }
}

bool8 IsRoamerAt(u32 roamerIndex, u8 mapGroup, u8 mapNum)
{
    if (ROAMER(roamerIndex)->active && mapGroup == sRoamerLocation[roamerIndex][MAP_GRP] && mapNum == sRoamerLocation[roamerIndex][MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

void CreateRoamerMonInstance(u32 roamerIndex)
{
    u32 status = ROAMER(roamerIndex)->statusA + (ROAMER(roamerIndex)->statusB << 8);
    struct Pokemon *mon = &gEnemyParty[0];
    ZeroEnemyPartyMons();
    CreateMonWithIVsPersonality(mon, ROAMER(roamerIndex)->species, ROAMER(roamerIndex)->level, ROAMER(roamerIndex)->ivs, ROAMER(roamerIndex)->personality);
    SetMonData(mon, MON_DATA_STATUS, &status);
    SetMonData(mon, MON_DATA_HP, &ROAMER(roamerIndex)->hp);
    SetMonData(mon, MON_DATA_COOL, &ROAMER(roamerIndex)->cool);
    SetMonData(mon, MON_DATA_BEAUTY, &ROAMER(roamerIndex)->beauty);
    SetMonData(mon, MON_DATA_CUTE, &ROAMER(roamerIndex)->cute);
    SetMonData(mon, MON_DATA_SMART, &ROAMER(roamerIndex)->smart);
    SetMonData(mon, MON_DATA_TOUGH, &ROAMER(roamerIndex)->tough);
    SetMonData(mon, MON_DATA_IS_SHINY, &ROAMER(roamerIndex)->shiny);
}

bool8 TryStartRoamerEncounter(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (IsRoamerAt(i, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum) == TRUE && (Random() % 4) == 0)
        {
            CreateRoamerMonInstance(i);
            gEncounteredRoamerIndex = i;
            return TRUE;
        }
    }
    return FALSE;
}

void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    u32 status = GetMonData(mon, MON_DATA_STATUS);

    ROAMER(gEncounteredRoamerIndex)->hp = GetMonData(mon, MON_DATA_HP);
    ROAMER(gEncounteredRoamerIndex)->statusA = status;
    ROAMER(gEncounteredRoamerIndex)->statusB = status >> 8;

    RoamerMoveToOtherLocationSet(gEncounteredRoamerIndex);
}

void SetRoamerInactive(u32 roamerIndex)
{
    ROAMER(roamerIndex)->active = FALSE;
}

void GetRoamerLocation(u32 roamerIndex, u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = sRoamerLocation[roamerIndex][MAP_GRP];
    *mapNum = sRoamerLocation[roamerIndex][MAP_NUM];
}

#define ROAMER_FLASH_VOBJ_ID 0xFF
#define ROAMER_FLASH_HORZ_SPEED 12
#define ROAMER_FLASH_VERT_SPEED 8

enum {
    ROAMER_FLASH_NONE,
    ROAMER_FLASH_CROSS_PATH,
    ROAMER_FLASH_RACE_PAST,
    ROAMER_FLASH_PEEK,
    ROAMER_FLASH_COUNT,
};

#define tSpriteId   data[0]
#define tDeltaX     data[1]
#define tDeltaY     data[2]
#define tFrames     data[3]
#define tMaxFrames  data[4]

static void DestroyRoamerFlashSprite(struct Sprite *sprite)
{
    u8 paletteNum = sprite->oam.paletteNum;
    u16 tileStart = sprite->sheetTileStart;
    DestroySprite(sprite);
    FieldEffectFreePaletteIfUnused(paletteNum);
    if (tileStart)
        FieldEffectFreeTilesIfUnused(tileStart);
}

static void Task_RoamerFlash(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct Sprite *sprite = &gSprites[task->tSpriteId];

    sprite->x += task->tDeltaX;
    sprite->y += task->tDeltaY;
    task->tFrames++;

    if (task->tFrames >= task->tMaxFrames)
    {
        DestroyRoamerFlashSprite(sprite);
        DestroyTask(taskId);
    }
}

enum {
    PEEK_PHASE_ENTER,
    PEEK_PHASE_LOOK_1,
    PEEK_PHASE_LOOK_2,
    PEEK_PHASE_EXIT,
};

#define tPhase      data[5]

static void Task_RoamerPeek(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct Sprite *sprite = &gSprites[task->tSpriteId];

    task->tFrames++;

    switch (task->tPhase)
    {
    case PEEK_PHASE_ENTER:
        sprite->y -= 3;
        if (task->tFrames >= 22)
        {
            task->tFrames = 0;
            task->tPhase = PEEK_PHASE_LOOK_1;
            TurnVirtualObject(ROAMER_FLASH_VOBJ_ID, DIR_WEST);
        }
        break;
    case PEEK_PHASE_LOOK_1:
        if (task->tFrames >= 10)
        {
            task->tFrames = 0;
            task->tPhase = PEEK_PHASE_LOOK_2;
            TurnVirtualObject(ROAMER_FLASH_VOBJ_ID, DIR_NORTH);
        }
        break;
    case PEEK_PHASE_LOOK_2:
        if (task->tFrames >= 8)
        {
            task->tFrames = 0;
            task->tPhase = PEEK_PHASE_EXIT;
            TurnVirtualObject(ROAMER_FLASH_VOBJ_ID, DIR_SOUTH);
        }
        break;
    case PEEK_PHASE_EXIT:
        sprite->y += 5;
        if (task->tFrames >= 28)
        {
            DestroyRoamerFlashSprite(sprite);
            DestroyTask(taskId);
        }
        break;
    }
}

// O S nao tem CountFreeSpriteTiles (o P sim, em sprite.c); sprite.c nao e deste
// pacote, entao a contagem e feita aqui pela API publica SpriteTileAllocBitmapOp.
static u16 CountFreeSpriteTiles(void)
{
    u16 i;
    u16 count = 0;

    for (i = gReservedSpriteTileCount; i < TOTAL_OBJ_TILE_COUNT; i++)
    {
        if (!SpriteTileAllocBitmapOp(i, 2))
            count++;
    }
    return count;
}

static u16 GetFirstRoamerSpeciesOnCurrentMap(void)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (IsRoamerAt(i, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
            return ROAMER(i)->species;
    }
    return SPECIES_NONE;
}

void TryShowRoamerFlash(void)
{
    u16 species = GetFirstRoamerSpeciesOnCurrentMap();
    u8 spriteId;
    u8 taskId;
    s16 startX, startY;
    s16 playerX = gSaveBlock1Ptr->pos.x;
    s16 playerY = gSaveBlock1Ptr->pos.y;
    u8 facing = GetPlayerFacingDirection();
    u8 flashType;
    s16 deltaX = 0;
    s16 deltaY = 0;
    s16 maxFrames = 0;
    enum Direction spriteDir;

    if (species == SPECIES_NONE)
        return;

    if (CountFreeSpriteTiles() < 64)
        return;

    flashType = Random() % ROAMER_FLASH_COUNT;

    if (flashType == ROAMER_FLASH_NONE)
        return;

    PlayCry_Normal(species, 0);

    if (flashType == ROAMER_FLASH_CROSS_PATH)
    {
        switch (facing)
        {
        case DIR_NORTH:
            startX = playerX + 10;
            startY = playerY - 7;
            deltaX = -ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_WEST;
            break;
        case DIR_SOUTH:
            startX = playerX - 10;
            startY = playerY + 7;
            deltaX = ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_EAST;
            break;
        case DIR_EAST:
            startX = playerX + 7;
            startY = playerY - 10;
            deltaY = ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_SOUTH;
            break;
        case DIR_WEST:
        default:
            startX = playerX - 7;
            startY = playerY - 10;
            deltaY = ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_SOUTH;
            break;
        }
        maxFrames = (20 * 16) / ROAMER_FLASH_VERT_SPEED;
    }
    else if (flashType == ROAMER_FLASH_RACE_PAST)
    {
        startY = playerY - 4;
        if (facing == DIR_EAST)
        {
            startX = playerX - 12;
            deltaX = ROAMER_FLASH_HORZ_SPEED;
            spriteDir = DIR_EAST;
        }
        else
        {
            startX = playerX + 12;
            deltaX = -ROAMER_FLASH_HORZ_SPEED;
            spriteDir = DIR_WEST;
        }
        maxFrames = (24 * 16) / ROAMER_FLASH_HORZ_SPEED;
    }
    else
    {
        if (facing == DIR_EAST || facing == DIR_SOUTH)
            startX = playerX + 6;
        else
            startX = playerX - 6;
        startY = playerY + 8;
        spriteDir = DIR_NORTH;
    }

    spriteId = CreateVirtualObject(
        OBJ_EVENT_MON + species,
        ROAMER_FLASH_VOBJ_ID,
        startX, startY,
        3, spriteDir
    );

    if (spriteId == MAX_SPRITES)
        return;

    if (OW_GFX_COMPRESS && gSprites[spriteId].sheetTileStart == TAG_NONE)
    {
        DestroyRoamerFlashSprite(&gSprites[spriteId]);
        return;
    }

    if (flashType == ROAMER_FLASH_PEEK)
    {
        taskId = CreateTask(Task_RoamerPeek, 80);
        gTasks[taskId].tSpriteId = spriteId;
        gTasks[taskId].tFrames = 0;
        gTasks[taskId].tPhase = PEEK_PHASE_ENTER;
    }
    else
    {
        taskId = CreateTask(Task_RoamerFlash, 80);
        gTasks[taskId].tSpriteId = spriteId;
        gTasks[taskId].tDeltaX = deltaX;
        gTasks[taskId].tDeltaY = deltaY;
        gTasks[taskId].tFrames = 0;
        gTasks[taskId].tMaxFrames = maxFrames;
    }
}

#undef tSpriteId
#undef tDeltaX
#undef tDeltaY
#undef tFrames
#undef tMaxFrames
#undef tPhase
