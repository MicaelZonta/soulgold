// Nexus trainer pool. CONTENT ONLY: the rules that use it are in src/nexus.c.
//
// Adding a trainer to the Nexus = one line here, after:
//   1. the team TRAINER_NEXUS_<NAME> in src/data/trainers.party (NEXUS_REGRAS
//      R10-R13) and its id in include/constants/opponents.h;
//   2. its generic fight Nexus_EventScript_<Name>_Fight in
//      data/scripts/nexus.inc (R16, the four rooms - not the champion room);
//   3. its sheet in .claude/rift_missions/nexus/<region>/<name>.md.
// A trainer's champion-room script is NOT here: it belongs to whichever
// legendary(s) it champions (src/data/nexus/legendaries.h), one script per
// legendary, because a trainer can champion more than one (NEXUS_REGRAS R16).
// Level scaling (R2) follows from this table: nothing else to register.
//
// X(ENUM_NAME, ScriptName, TRAINER_ID, OBJ_EVENT_GFX)
#define NEXUS_TRAINER_LIST(X)                                               \
    X(COLRESS, Colress, TRAINER_NEXUS_COLRESS, OBJ_EVENT_GFX_COLRESS)       \
    X(BRUNO,   Bruno,   TRAINER_NEXUS_BRUNO,   OBJ_EVENT_GFX_BRUNO)         \
    X(ELESA,   Elesa,   TRAINER_NEXUS_ELESA,   OBJ_EVENT_GFX_ELESA)         \
    X(VOLKNER, Volkner, TRAINER_NEXUS_VOLKNER, OBJ_EVENT_GFX_VOLKNER)       \
    X(STEVEN,  Steven,  TRAINER_NEXUS_STEVEN,  OBJ_EVENT_GFX_STEVEN)        \
    X(RAMOS,   Ramos,   TRAINER_NEXUS_RAMOS,   OBJ_EVENT_GFX_RAMOS)         \
    X(GUZMA,   Guzma,   TRAINER_NEXUS_GUZMA,   OBJ_EVENT_GFX_GUZMA)         \
    X(SOLIERA, Soliera, TRAINER_NEXUS_SOLIERA, OBJ_EVENT_GFX_SOLIERA)       \
    X(BYRON,   Byron,   TRAINER_NEXUS_BYRON,   OBJ_EVENT_GFX_BYRON)         \
    X(FANTINA, Fantina, TRAINER_NEXUS_FANTINA, OBJ_EVENT_GFX_FANTINA)       \
    X(RED, Red, TRAINER_NEXUS_RED, OBJ_EVENT_GFX_RED)                      \
    X(BLUE, Blue, TRAINER_NEXUS_BLUE, OBJ_EVENT_GFX_BLUE)                  \
    X(BROCK, Brock, TRAINER_NEXUS_BROCK, OBJ_EVENT_GFX_BROCK)              \
    X(MISTY, Misty, TRAINER_NEXUS_MISTY, OBJ_EVENT_GFX_MISTY)              \
    X(LT_SURGE, LtSurge, TRAINER_NEXUS_LT_SURGE, OBJ_EVENT_GFX_SURGE)      \
    X(ERIKA, Erika, TRAINER_NEXUS_ERIKA, OBJ_EVENT_GFX_ERIKA)              \
    X(KOGA, Koga, TRAINER_NEXUS_KOGA, OBJ_EVENT_GFX_KOGA)                  \
    X(SABRINA, Sabrina, TRAINER_NEXUS_SABRINA, OBJ_EVENT_GFX_SABRINA)      \
    X(BLAINE, Blaine, TRAINER_NEXUS_BLAINE, OBJ_EVENT_GFX_BLAINE)          \
    X(GIOVANNI, Giovanni, TRAINER_NEXUS_GIOVANNI, OBJ_EVENT_GFX_GIOVANNI)  \
    X(LANCE, Lance, TRAINER_NEXUS_LANCE, OBJ_EVENT_GFX_LANCE)              \
    X(ARCHER, Archer, TRAINER_NEXUS_ARCHER, OBJ_EVENT_GFX_ARCHER)          \
    X(ARIANA, Ariana, TRAINER_NEXUS_ARIANA, OBJ_EVENT_GFX_ARIANA)          \
    X(PROTON, Proton, TRAINER_NEXUS_PROTON, OBJ_EVENT_GFX_PROTON)          \
    X(PETREL, Petrel, TRAINER_NEXUS_PETREL, OBJ_EVENT_GFX_PETREL)          \
    X(SILVER, Silver, TRAINER_NEXUS_SILVER, OBJ_EVENT_GFX_SILVER)          \
    X(FALKNER, Falkner, TRAINER_NEXUS_FALKNER, OBJ_EVENT_GFX_FALKNER)      \
    X(BUGSY, Bugsy, TRAINER_NEXUS_BUGSY, OBJ_EVENT_GFX_BUGSY)              \
    X(WHITNEY, Whitney, TRAINER_NEXUS_WHITNEY, OBJ_EVENT_GFX_WHITNEY)      \
    X(MORTY, Morty, TRAINER_NEXUS_MORTY, OBJ_EVENT_GFX_MORTY)              \
    X(CHUCK, Chuck, TRAINER_NEXUS_CHUCK, OBJ_EVENT_GFX_CHUCK)              \
    X(JASMINE, Jasmine, TRAINER_NEXUS_JASMINE, OBJ_EVENT_GFX_JASMINE)      \
    X(PRYCE, Pryce, TRAINER_NEXUS_PRYCE, OBJ_EVENT_GFX_PRYCE)              \
    X(CLAIR, Clair, TRAINER_NEXUS_CLAIR, OBJ_EVENT_GFX_CLAIR)              \
    X(WILL, Will, TRAINER_NEXUS_WILL, OBJ_EVENT_GFX_WILL)                  \
    X(KAREN, Karen, TRAINER_NEXUS_KAREN, OBJ_EVENT_GFX_KAREN)              \
    X(EUSINE, Eusine, TRAINER_NEXUS_EUSINE, OBJ_EVENT_GFX_EUSINE)          \
    X(BRENDAN, Brendan, TRAINER_NEXUS_BRENDAN, OBJ_EVENT_GFX_BRENDAN_HOENN) \
    X(MAY, May, TRAINER_NEXUS_MAY, OBJ_EVENT_GFX_LINK_RS_MAY)              \
    X(WALLY, Wally, TRAINER_NEXUS_WALLY, OBJ_EVENT_GFX_WALLY)              \
    X(ROXANNE, Roxanne, TRAINER_NEXUS_ROXANNE, OBJ_EVENT_GFX_ROXANNE)      \
    X(BRAWLY, Brawly, TRAINER_NEXUS_BRAWLY, OBJ_EVENT_GFX_BRAWLY)          \
    X(WATTSON, Wattson, TRAINER_NEXUS_WATTSON, OBJ_EVENT_GFX_WATTSON)      \
    X(FLANNERY, Flannery, TRAINER_NEXUS_FLANNERY, OBJ_EVENT_GFX_FLANNERY)  \
    X(NORMAN, Norman, TRAINER_NEXUS_NORMAN, OBJ_EVENT_GFX_NORMAN)          \
    X(WINONA, Winona, TRAINER_NEXUS_WINONA, OBJ_EVENT_GFX_WINONA)          \
    X(TATE_AND_LIZA, TateAndLiza, TRAINER_NEXUS_TATE_AND_LIZA, OBJ_EVENT_GFX_TATE) \
    X(WALLACE, Wallace, TRAINER_NEXUS_WALLACE, OBJ_EVENT_GFX_WALLACE)      \
    X(JUAN, Juan, TRAINER_NEXUS_JUAN, OBJ_EVENT_GFX_JUAN)                  \
    X(SIDNEY, Sidney, TRAINER_NEXUS_SIDNEY, OBJ_EVENT_GFX_SIDNEY)          \
    X(PHOEBE, Phoebe, TRAINER_NEXUS_PHOEBE, OBJ_EVENT_GFX_PHOEBE)          \
    X(GLACIA, Glacia, TRAINER_NEXUS_GLACIA, OBJ_EVENT_GFX_GLACIA)          \
    X(DRAKE, Drake, TRAINER_NEXUS_DRAKE, OBJ_EVENT_GFX_DRAKE)              \
    X(NOLAND, Noland, TRAINER_NEXUS_NOLAND, OBJ_EVENT_GFX_NOLAND)          \
    X(GRETA, Greta, TRAINER_NEXUS_GRETA, OBJ_EVENT_GFX_GRETA)              \
    X(TUCKER, Tucker, TRAINER_NEXUS_TUCKER, OBJ_EVENT_GFX_TUCKER)          \
    X(LUCY, Lucy, TRAINER_NEXUS_LUCY, OBJ_EVENT_GFX_LUCY)                  \
    X(SPENSER, Spenser, TRAINER_NEXUS_SPENSER, OBJ_EVENT_GFX_SPENSER)      \
    X(BRANDON, Brandon, TRAINER_NEXUS_BRANDON, OBJ_EVENT_GFX_BRANDON)      \
    X(ANABEL, Anabel, TRAINER_NEXUS_ANABEL, OBJ_EVENT_GFX_ANABEL)          \
    X(MAXIE, Maxie, TRAINER_NEXUS_MAXIE, OBJ_EVENT_GFX_MAXIE)              \
    X(ARCHIE, Archie, TRAINER_NEXUS_ARCHIE, OBJ_EVENT_GFX_ARCHIE)          \
    X(GLADION, Gladion, TRAINER_NEXUS_GLADION, OBJ_EVENT_GFX_GLADION)      \
    X(KUKUI, Kukui, TRAINER_NEXUS_KUKUI, OBJ_EVENT_GFX_KUKUI)              \
    X(LUSAMINE, Lusamine, TRAINER_NEXUS_LUSAMINE, OBJ_EVENT_GFX_LUSAMINE)  \
    X(JANINE, Janine, TRAINER_NEXUS_JANINE, OBJ_EVENT_GFX_JANINE)          \
    X(LEAF, Leaf, TRAINER_NEXUS_LEAF, OBJ_EVENT_GFX_LEAF)                  \
    X(AZ, AZ, TRAINER_NEXUS_AZ, OBJ_EVENT_GFX_AZ)                          \
    X(AGATHA, Agatha, TRAINER_NEXUS_AGATHA, OBJ_EVENT_GFX_AGATHA)          \
    X(ALDER, Alder, TRAINER_NEXUS_ALDER, OBJ_EVENT_GFX_ALDER)              \
    X(ALLISTER, Allister, TRAINER_NEXUS_ALLISTER, OBJ_EVENT_GFX_ALISTER)   \
    X(AVERY, Avery, TRAINER_NEXUS_AVERY, OBJ_EVENT_GFX_AVERY)              \
    X(BARRY, Barry, TRAINER_NEXUS_BARRY, OBJ_EVENT_GFX_BARRY)              \
    X(BEA, Bea, TRAINER_NEXUS_BEA, OBJ_EVENT_GFX_BEA)                      \
    X(BRYCEN, Brycen, TRAINER_NEXUS_BRYCEN, OBJ_EVENT_GFX_BRYCEN)          \
    X(CHEREN, Cheren, TRAINER_NEXUS_CHEREN, OBJ_EVENT_GFX_CHEREN)          \
    X(CILAN, Cilan, TRAINER_NEXUS_CILAN, OBJ_EVENT_GFX_CILAN)              \
    X(CYNTHIA, Cynthia, TRAINER_NEXUS_CYNTHIA, OBJ_EVENT_GFX_CYNTHIA)      \
    X(CYRUS, Cyrus, TRAINER_NEXUS_CYRUS, OBJ_EVENT_GFX_CYRUS)              \
    X(DAWN, Dawn, TRAINER_NEXUS_DAWN, OBJ_EVENT_GFX_DAWN)                  \
    X(DIANTHA, Diantha, TRAINER_NEXUS_DIANTHA, OBJ_EVENT_GFX_DIANTHA)      \
    X(GARDENIA, Gardenia, TRAINER_NEXUS_GARDENIA, OBJ_EVENT_GFX_GARDENIA)  \
    X(GHETSIS, Ghetsis, TRAINER_NEXUS_GHETSIS, OBJ_EVENT_GFX_GHETSIS)      \
    X(GLORIA, Gloria, TRAINER_NEXUS_GLORIA, OBJ_EVENT_GFX_GLORIA)          \
    X(GRUSHA, Grusha, TRAINER_NEXUS_GRUSHA, OBJ_EVENT_GFX_GRUSHA)          \
    X(HASSEL, Hassel, TRAINER_NEXUS_HASSEL, OBJ_EVENT_GFX_HASSEL)          \
    X(HAU, Hau, TRAINER_NEXUS_HAU, OBJ_EVENT_GFX_HAU)                      \
    X(HILDA, Hilda, TRAINER_NEXUS_HILDA, OBJ_EVENT_GFX_HILDA)              \
    X(HOP, Hop, TRAINER_NEXUS_HOP, OBJ_EVENT_GFX_HOP)                      \
    X(IONO, Iono, TRAINER_NEXUS_IONO, OBJ_EVENT_GFX_IONO)                  \
    X(IRIS, Iris, TRAINER_NEXUS_IRIS, OBJ_EVENT_GFX_IRIS)                  \
    X(JESSIE_JAMES, JessieJames, TRAINER_NEXUS_JESSIE_JAMES, OBJ_EVENT_GFX_JESSIE)\
    X(JUNIPER, Juniper, TRAINER_NEXUS_JUNIPER, OBJ_EVENT_GFX_JUNIPER)      \
    X(KATY, Katy, TRAINER_NEXUS_KATY, OBJ_EVENT_GFX_KATY)                  \
    X(KLARA, Klara, TRAINER_NEXUS_KLARA, OBJ_EVENT_GFX_KLARA)              \
    X(KORRINA, Korrina, TRAINER_NEXUS_KORRINA, OBJ_EVENT_GFX_KORRINA)      \
    X(LARRY, Larry, TRAINER_NEXUS_LARRY, OBJ_EVENT_GFX_LARRY)              \
    X(LENORA, Lenora, TRAINER_NEXUS_LENORA, OBJ_EVENT_GFX_LENORA)          \
    X(LEON, Leon, TRAINER_NEXUS_LEON, OBJ_EVENT_GFX_LEON)                  \
    X(LORELEI, Lorelei, TRAINER_NEXUS_LORELEI, OBJ_EVENT_GFX_LORELEI)      \
    X(LYSANDRE, Lysandre, TRAINER_NEXUS_LYSANDRE, OBJ_EVENT_GFX_LYSANDRE)  \
    X(MARNIE, Marnie, TRAINER_NEXUS_MARNIE, OBJ_EVENT_GFX_MARNIE)          \
    X(MELONY, Melony, TRAINER_NEXUS_MELONY, OBJ_EVENT_GFX_MELONY)          \
    X(MOLLY, Molly, TRAINER_NEXUS_MOLLY, OBJ_EVENT_GFX_MOLLY_HALE)         \
    X(MUSTARD, Mustard, TRAINER_NEXUS_MUSTARD, OBJ_EVENT_GFX_MUSTARD)      \
    X(N, N, TRAINER_NEXUS_N, OBJ_EVENT_GFX_N)                              \
    X(NEMONA, Nemona, TRAINER_NEXUS_NEMONA, OBJ_EVENT_GFX_NEMONA)          \
    X(NESSA, Nessa, TRAINER_NEXUS_NESSA, OBJ_EVENT_GFX_NESSA)              \
    X(OLIVIA, Olivia, TRAINER_NEXUS_OLIVIA, OBJ_EVENT_GFX_OLIVIA)          \
    X(PEONIA, Peonia, TRAINER_NEXUS_PEONIA, OBJ_EVENT_GFX_PEONIA)          \
    X(PEONY, Peony, TRAINER_NEXUS_PEONY, OBJ_EVENT_GFX_PEONY)              \
    X(ROWAN, Rowan, TRAINER_NEXUS_ROWAN, OBJ_EVENT_GFX_ROWAN)              \
    X(ROSA, Rosa, TRAINER_NEXUS_ROSA, OBJ_EVENT_GFX_ROSA)                  \
    X(SERENA, Serena, TRAINER_NEXUS_SERENA, OBJ_EVENT_GFX_SERENA)          \
    X(SHELLY, Shelly, TRAINER_NEXUS_SHELLY, OBJ_EVENT_GFX_SHELLY)          \
    X(SKYLA, Skyla, TRAINER_NEXUS_SKYLA, OBJ_EVENT_GFX_SKYLA)              \
    X(TULIP, Tulip, TRAINER_NEXUS_TULIP, OBJ_EVENT_GFX_TULIP)              \
    X(VALERIE, Valerie, TRAINER_NEXUS_VALERIE, OBJ_EVENT_GFX_VALERIE)      \
    X(VIOLA, Viola, TRAINER_NEXUS_VIOLA, OBJ_EVENT_GFX_VIOLA)              \
    X(ZINNIA, Zinnia, TRAINER_NEXUS_ZINNIA, OBJ_EVENT_GFX_ZINNIA)          \
    X(LILLIE, Lillie, TRAINER_NEXUS_LILLIE, OBJ_EVENT_GFX_LILLIE)

#define NEXUS_TRAINER_ENUM(ENUM, Name, id, gfx) NEXUS_TRAINER_##ENUM,
enum
{
    NEXUS_TRAINER_LIST(NEXUS_TRAINER_ENUM)
    NEXUS_TRAINER_COUNT
};
#undef NEXUS_TRAINER_ENUM

#define NEXUS_TRAINER_SCRIPTS(ENUM, Name, id, gfx)          \
    extern const u8 Nexus_EventScript_##Name##_Fight[];
NEXUS_TRAINER_LIST(NEXUS_TRAINER_SCRIPTS)
#undef NEXUS_TRAINER_SCRIPTS

#define NEXUS_TRAINER_ENTRY(ENUM, Name, id, gfx)                    \
    [NEXUS_TRAINER_##ENUM] =                                        \
    {                                                               \
        .trainerId = id,                                            \
        .graphicsId = gfx,                                          \
        .fightScript = Nexus_EventScript_##Name##_Fight,            \
    },
const struct NexusTrainer gNexusTrainers[NEXUS_TRAINER_COUNT] =
{
    NEXUS_TRAINER_LIST(NEXUS_TRAINER_ENTRY)
};
#undef NEXUS_TRAINER_ENTRY
