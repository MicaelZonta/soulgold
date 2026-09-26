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
};
