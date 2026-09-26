// O texto que a plaquinha mostra. A ordem tem que bater com
// include/constants/speaker_names.h e com o bloco de nomes em charmap.txt.
// A plaquinha usa FONT_SMALL e no maximo OW_NAME_BOX_DEFAULT_WIDTH tiles
// (include/config/name_box.h): nomes curtos.
const u8 *const gSpeakerNamesTable[SP_NAME_COUNT] =
{
    [SP_NAME_MOM]     = COMPOUND_STRING("Mom"),
    [SP_NAME_PLAYER]  = COMPOUND_STRING("{PLAYER}"),
    [SP_NAME_LOOKER]  = COMPOUND_STRING("Looker"),
    [SP_NAME_ANABEL]  = COMPOUND_STRING("Anabel"),
    [SP_NAME_LILLIE]  = COMPOUND_STRING("Lillie"),
    [SP_NAME_GLADION] = COMPOUND_STRING("Gladion"),
    [SP_NAME_KUKUI]   = COMPOUND_STRING("Kukui"),
    [SP_NAME_PRYCE]   = COMPOUND_STRING("Pryce"),
    [SP_NAME_CLAIR]   = COMPOUND_STRING("Clair"),
    [SP_NAME_OLD_MAN] = COMPOUND_STRING("Old man"),
    [SP_NAME_ELM]      = COMPOUND_STRING("Elm"),
    [SP_NAME_LUSAMINE] = COMPOUND_STRING("Lusamine"),
    [SP_NAME_KURT]     = COMPOUND_STRING("Kurt"),
    [SP_NAME_HECTOR]   = COMPOUND_STRING("Hector"),
    [SP_NAME_BOY]      = COMPOUND_STRING("Boy"),
    // Gold or Crystal, the rival next door. Expanded at draw time by
    // StringExpandPlaceholders (ExpandPlaceholder_Neighbor, src/string_util.c).
    [SP_NAME_NEIGHBOR] = COMPOUND_STRING("{NEIGHBOR}"),
    [SP_NAME_SAILOR]   = COMPOUND_STRING("Sailor"),
    [SP_NAME_COLRESS]  = COMPOUND_STRING("Colress"),
    [SP_NAME_BRUNO]    = COMPOUND_STRING("Bruno"),
    [SP_NAME_ELESA]    = COMPOUND_STRING("Elesa"),
    [SP_NAME_VOLKNER]  = COMPOUND_STRING("Volkner"),
    [SP_NAME_STEVEN]   = COMPOUND_STRING("Steven"),
    [SP_NAME_RAMOS]    = COMPOUND_STRING("Ramos"),
    [SP_NAME_GUZMA]    = COMPOUND_STRING("Guzma"),
    [SP_NAME_SOLIERA]  = COMPOUND_STRING("Soliera"),
    [SP_NAME_BYRON]    = COMPOUND_STRING("Byron"),
    [SP_NAME_FANTINA]  = COMPOUND_STRING("Fantina"),
};
