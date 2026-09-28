#ifndef GUARD_CONSTANTS_SPEAKER_NAMES_H
#define GUARD_CONSTANTS_SPEAKER_NAMES_H

// Nomes que podem aparecer na plaquinha acima da caixa de dialogo.
//
// Tres arquivos precisam concordar, NA MESMA ORDEM:
//   1. este enum                      SP_NAME_LILLIE
//   2. src/data/speaker_names.h       o texto que aparece na tela
//   3. charmap.txt                    NAME_LILLIE, para escrever {SPEAKER NAME_LILLIE}
//
// Nao reordene nem remova entradas: o byte gravado no texto e o indice deste
// enum, entao mexer na ordem troca o nome de toda fala ja escrita. Sempre
// ACRESCENTE antes de SP_NAME_COUNT.
//
// Para adicionar um falante, use o ajudante da skill `nomear-falante`, que
// edita os tres arquivos de uma vez e confere o resultado:
//   python3 .claude/skills/nomear-falante/adicionar_falante.py PRYCE "Pryce"
//   python3 .claude/skills/nomear-falante/checar_falantes.py
enum SpeakerNames {
    SP_NAME_NONE = 0,
    SP_NAME_MOM,
    SP_NAME_PLAYER,
    SP_NAME_LOOKER,
    SP_NAME_ANABEL,
    SP_NAME_LILLIE,
    SP_NAME_GLADION,
    SP_NAME_KUKUI,
    SP_NAME_PRYCE,
    SP_NAME_CLAIR,
    SP_NAME_OLD_MAN,
    SP_NAME_ELM,
    SP_NAME_LUSAMINE,
    SP_NAME_KURT,
    SP_NAME_HECTOR,
    SP_NAME_BOY,
    SP_NAME_NEIGHBOR,   // Gold or Crystal: the plaque is "{NEIGHBOR}", resolved per player gender
    SP_NAME_SAILOR,
    SP_NAME_COLRESS,
    SP_NAME_BRUNO,
    SP_NAME_ELESA,
    SP_NAME_VOLKNER,
    SP_NAME_STEVEN,
    SP_NAME_RAMOS,
    SP_NAME_GUZMA,
    SP_NAME_SOLIERA,
    SP_NAME_BYRON,
    SP_NAME_FANTINA,
    SP_NAME_OAK,
    SP_NAME_FLORIST,
    SP_NAME_ELDER,          // Dragon's Den Master (Clair's grandfather)
    SP_NAME_CHUCKS_WIFE,
    SP_NAME_OFFICER,        // generic police officer (Sun and Moon Altar)
    SP_NAME_AETHER,         // generic Aether Foundation staff (Sun and Moon Altar)
    SP_NAME_RED,
    SP_NAME_BLUE,
    SP_NAME_BROCK,
    SP_NAME_MISTY,
    SP_NAME_LT_SURGE,
    SP_NAME_ERIKA,
    SP_NAME_KOGA,
    SP_NAME_SABRINA,
    SP_NAME_BLAINE,
    SP_NAME_GIOVANNI,
    SP_NAME_LANCE,
    SP_NAME_ARCHER,
    SP_NAME_ARIANA,
    SP_NAME_PROTON,
    SP_NAME_PETREL,
    SP_NAME_SILVER,
    SP_NAME_FALKNER,
    SP_NAME_BUGSY,
    SP_NAME_WHITNEY,
    SP_NAME_MORTY,
    SP_NAME_CHUCK,
    SP_NAME_JASMINE,
    SP_NAME_WILL,
    SP_NAME_KAREN,
    SP_NAME_EUSINE,
    SP_NAME_BRENDAN,
    SP_NAME_MAY,
    SP_NAME_WALLY,
    SP_NAME_ROXANNE,
    SP_NAME_BRAWLY,
    SP_NAME_WATTSON,
    SP_NAME_FLANNERY,
    SP_NAME_NORMAN,
    SP_NAME_WINONA,
    SP_NAME_TATE_AND_LIZA,
    SP_NAME_WALLACE,
    SP_NAME_JUAN,
    SP_NAME_SIDNEY,
    SP_NAME_PHOEBE,
    SP_NAME_GLACIA,
    SP_NAME_DRAKE,
    SP_NAME_NOLAND,
    SP_NAME_GRETA,
    SP_NAME_TUCKER,
    SP_NAME_LUCY,
    SP_NAME_SPENSER,
    SP_NAME_BRANDON,
    SP_NAME_MAXIE,
    SP_NAME_ARCHIE,
    SP_NAME_JANINE,
    SP_NAME_GREEN,
    SP_NAME_COUNT
};

#endif // GUARD_CONSTANTS_SPEAKER_NAMES_H
