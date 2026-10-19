// Add new IDs here
enum {
    HELP_START_MENU,
    HELP_MEGA_EVOLUTION,
    HELP_MASTER_BALL,
    HELP_GIMMIGHOUL_COINS,
    HELP_TELEPORTER_WINDOW,
    HELP_ALOLA_WINDOW,
    HELP_COUNT
};

// Add entries here
// These entries are example entries which you can replace, but they exist to get you started.
const struct HelpWindow gHelpWindowInfo[] =
{
    [HELP_START_MENU] =
    {
        .header = COMPOUND_STRING("Information: Pokédex"),
        .desc = COMPOUND_STRING("To access the Pokédex, press {START_BUTTON}\n"
                                "while you're in the overworld!"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL
    },
    [HELP_MEGA_EVOLUTION] =
    {
        .header = COMPOUND_STRING("Information: Mega Evolution"),
        .desc = COMPOUND_STRING("In battle, press {START_BUTTON} to Mega Evolve!\n\n"
                                "The Pokémon must hold their Mega Stone\n"
                                "to be able to Mega Evolve.\n"
                                "You can only Mega Evolve once per battle."
                            ),
    },
    [HELP_MASTER_BALL] =
    {
        .header = COMPOUND_STRING("Information: Master Ball"),
        .desc = COMPOUND_STRING("There is only one Master Ball in Pokémon;\n"
                                "use it wisely!\n"
                                "Professor Oak suggests using it on a Pokémon\n"
                                "you want to add to your team but are hard to\n"
                                "catch, like a Fearow or Tentacruel!"
                            ),
    },
    [HELP_GIMMIGHOUL_COINS] =
    {
        .header = COMPOUND_STRING("Information: Evolving Gimmighoul into Gholdengo"),
        .desc = COMPOUND_STRING("To evolve Gimmighoul into Gholdengo, you\n"
                                "need to gather 999 {COLOR RED}Gimmighoul Coins{COLOR DARK_GRAY}.\n\n"
                                "You can find Gimmighoul Coins scattered\n"
                                "all around Paldea."
                            ),
        .headerFont = FONT_NARROWER,
    },
    [HELP_TELEPORTER_WINDOW] =
    {
        .header = COMPOUND_STRING("Optional bonus content: Teleporter"),
        .desc = COMPOUND_STRING("The Teleporter can PERMANENTLY change\n"
                                "Pokémon into their Galarian forms.\n"
                                "Galarian forms are NOT required\n"
                                "for story progression or\n"
                                "National Pokédex completion.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
    },
    [HELP_ALOLA_WINDOW] =
    {
        .header = COMPOUND_STRING("Optional bonus content: Isles"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "bonus content: Isles.\n"
                                "It is NOT required for story\n"
                                "or National Pokédex completion.\n"
                                "\n"
                                "It's just a bonus. If you want it."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
    },
    // Add more entries
};