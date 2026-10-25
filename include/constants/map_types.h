#ifndef GUARD_CONSTANTS_MAP_TYPES_H
#define GUARD_CONSTANTS_MAP_TYPES_H

enum MapType
{
    MAP_TYPE_NONE,
    MAP_TYPE_TOWN,
    MAP_TYPE_CITY,
    MAP_TYPE_ROUTE,
    MAP_TYPE_UNDERGROUND,
    MAP_TYPE_UNDERWATER,
    MAP_TYPE_OCEAN_ROUTE,
    MAP_TYPE_UNKNOWN, // Not used by any map.
    MAP_TYPE_INDOOR,
    MAP_TYPE_SECRET_BASE,
};

enum MapBattleScene
{
    MAP_BATTLE_SCENE_NORMAL,
    MAP_BATTLE_SCENE_GYM,
    MAP_BATTLE_SCENE_MAGMA,
    MAP_BATTLE_SCENE_AQUA,
    MAP_BATTLE_SCENE_SIDNEY,
    MAP_BATTLE_SCENE_PHOEBE,
    MAP_BATTLE_SCENE_GLACIA,
    MAP_BATTLE_SCENE_DRAKE,
    MAP_BATTLE_SCENE_WILL,
    MAP_BATTLE_SCENE_KOGA,
    MAP_BATTLE_SCENE_BRUNO,
    MAP_BATTLE_SCENE_KAREN,
    MAP_BATTLE_SCENE_FRONTIER,
    MAP_BATTLE_SCENE_ULTRA_SPACE,   // UltraSpaceArena: rift + gold stages (BATTLE_ENVIRONMENT_ULTRA_SPACE)
    // Ambientes trazidos do HnS 2.0.6 em 25/10/2026. Com a arte classica,
    // GRAY_CAVE e GRAY_CAVE_WATER desenham a caverna normal; e com a arte
    // "modern" ligada que elas ficam cinza.
    MAP_BATTLE_SCENE_GRAY_CAVE,
    MAP_BATTLE_SCENE_CAVE_WATER,
    MAP_BATTLE_SCENE_GRAY_CAVE_WATER,
    MAP_BATTLE_SCENE_ROCK_SNOW,
};

// Nao e pendencia: o HnS define exatamente igual (map_types.h deles), nao ha
// cenario dedicado do outro lado para portar.
#define MAP_BATTLE_SCENE_INDOOR_2 MAP_BATTLE_SCENE_NORMAL

#endif  // GUARD_CONSTANTS_MAP_TYPES_H
