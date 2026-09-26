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
    SP_NAME_COUNT
};

#endif // GUARD_CONSTANTS_SPEAKER_NAMES_H
