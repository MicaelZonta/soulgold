#include "global.h"
#include "agb_flash.h"
#include "credits.h"
#include "event_data.h"
#include "hall_of_fame.h"
#include "link.h"
#include "main.h"
#include "gba/flash_internal.h"
#include "malloc.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "overworld.h"
#include "save.h"
#include "start_menu.h"
#include "task.h"
#include "trade.h"
#include "mystery_gift_menu.h"
#include "union_room_chat.h"
#include "test/test.h"
#include "constants/characters.h"
#include "constants/game_stat.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
// SoulGold: +8 ObjectEvents in objectEventsExtra (16 -> 24) e o resto do fork (conferido em 31/10/2026, depois do merge do upstream).
#define T_SAVEBLOCK1_SIZE 16396
// SoulGold: FREE_EXTRA_SEEN_FLAGS_SAVEBLOCK2 (-104) and Candy Jar removed from SaveBlock3 (-4).
#define T_SAVEBLOCK2_SIZE 2760
#define T_SAVEBLOCK3_SIZE 96
#define T_POKEMONSTORAGE_SIZE 43456

TEST("SaveBlock1 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), T_SAVEBLOCK1_SIZE);
}

TEST("SaveBlock2 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock2), T_SAVEBLOCK2_SIZE);
}

TEST("SaveBlock3 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock3), T_SAVEBLOCK3_SIZE);
}

TEST("PokemonStorage is backwards compatible")
{
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
}

#undef T_SAVEBLOCK1_SIZE
#undef T_SAVEBLOCK2_SIZE
#undef T_SAVEBLOCK3_SIZE
#undef T_POKEMONSTORAGE_SIZE

