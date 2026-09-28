// Nexus prize (R9): one item for winning the five fights AND catching the
// legendary. CONTENT ONLY: drawn by Nexus_GetPrize in src/nexus.c.
//
// A group is a run of consecutive item ids; the day picks a group by weight,
// then one item of it. Same day -> same prize.
//
// Not here on purpose: Bottle Caps (they do nothing yet, R9) and Poke Balls in
// quantity (R14). Herbs lower IVs; add them only if the author asks.

static const struct NexusPrizeGroup sNexusPrizeGroups[] =
{
    { .firstItem = ITEM_LONELY_MINT,    .count = ITEM_SERIOUS_MINT - ITEM_LONELY_MINT + 1,  .weight = 2 }, // 21 Mints
    { .firstItem = ITEM_HEALTH_FEATHER, .count = ITEM_SWIFT_FEATHER - ITEM_HEALTH_FEATHER + 1, .weight = 2 }, // +5 IV Feathers
    { .firstItem = ITEM_TM01,           .count = NUM_TECHNICAL_MACHINES,                   .weight = 1 }, // TMs
};
