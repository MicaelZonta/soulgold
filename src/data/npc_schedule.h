// A agenda de cada personagem que roda pelo mundo.
//
// Regras da tabela:
//  - As fatias de um personagem sao lidas na ordem; a primeira que casar com o
//    dia E a hora ganha. Entao a ultima fatia pode ser o "resto da semana".
//  - REGRA DO AUTOR: um personagem de agenda tem que estar em ALGUM lugar
//    sempre. A ultima fatia de cada um e um curinga (SCHED_EVERY_DAY +
//    SCHED_ANY_TIME) que cobre o que sobrou, entao nao existe horario em que
//    ele desapareca do mundo. Quem acrescentar personagem aqui mantem isso:
//    o teste e simples, as 7 x 4 combinacoes tem que casar com alguma fatia.
//  - O mapa so precisa estar aqui se o object_event dele existir la, escondido
//    por FLAG_TEMP_D.

static const struct NpcScheduleSlot sFlannerySchedule[] =
{
    // Quarta-feira ela passa o dia com o Blaine. Foi ele quem fez a charada
    // que comecou tudo, e os dois nao param de discutir sobre vapor.
    { SCHED_WED,                       SCHED_ANY_TIME, MAP_GROUP(MAP_SEAFOAM_ISLANDS_GYM),  MAP_NUM(MAP_SEAFOAM_ISLANDS_GYM)  },

    // De dia ela esta onde tem trabalho: a encosta do Mt. Ember.
    { SCHED_MON | SCHED_TUE | SCHED_THU | SCHED_FRI,
                                       SCHED_DAYLIGHT, MAP_GROUP(MAP_MT_EMBER_EXTERIOR),    MAP_NUM(MAP_MT_EMBER_EXTERIOR)    },

    // Fim de semana de dia ela desce para a ilha queimada, que e o assunto
    // predileto dela: um vulcao que ja explodiu e ninguem leu a tempo.
    { SCHED_WEEKEND,                   SCHED_DAYLIGHT, MAP_GROUP(MAP_CINNABAR_ISLAND),      MAP_NUM(MAP_CINNABAR_ISLAND)      },

    // Toda noite, sem excecao, ela termina nas termas. E o ritual dela.
    { SCHED_EVERY_DAY,                 SCHED_DARK,     MAP_GROUP(MAP_NEWSINJOH_HOTSPRINGS), MAP_NUM(MAP_NEWSINJOH_HOTSPRINGS) },
};

// Os dois que ficaram na Birth Island depois da historia. Nenhum dos dois
// existia em lugar nenhum do mundo antes disto.
//
// Os dois tem dia E hora, nao so dia, e os horarios dizem quem e cada um.
// O Colress trabalha de dia, porque e quando da para ler instrumento. A
// Soliera monta guarda a noite, porque foi uma luz que a trouxe ate aqui e e
// no escuro que da para ver luz. Entao eles quase nao se encontram - e sabado
// e o unico dia em que os turnos se tocam, de tarde, que e quando o jogador
// pode ver os dois discordando sobre o que fazer com a cratera.

static const struct NpcScheduleSlot sColressSchedule[] =
{
    // Sabado ele estica ate a tarde, e e so por isso que os dois se cruzam.
    { SCHED_SAT,                                     SCHED_DAYLIGHT | SCHED_EVENING,
      MAP_GROUP(MAP_BIRTH_ISLAND_EXTERIOR), MAP_NUM(MAP_BIRTH_ISLAND_EXTERIOR) },
    { SCHED_MON | SCHED_WED | SCHED_FRI,             SCHED_DAYLIGHT,
      MAP_GROUP(MAP_BIRTH_ISLAND_EXTERIOR), MAP_NUM(MAP_BIRTH_ISLAND_EXTERIOR) },
    // O resto da semana no laboratorio das Ruinas de Alph, que ja e cheio de
    // gente estudando uma escrita que ninguem decifrou. Ele e visita e esta
    // usando o equipamento dos outros.
    { SCHED_EVERY_DAY,                               SCHED_ANY_TIME,
      MAP_GROUP(MAP_RUINS_OF_ALPH_LAB), MAP_NUM(MAP_RUINS_OF_ALPH_LAB) },
};

static const struct NpcScheduleSlot sSolieraSchedule[] =
{
    { SCHED_TUE | SCHED_THU | SCHED_SAT,             SCHED_DARK,
      MAP_GROUP(MAP_BIRTH_ISLAND_EXTERIOR), MAP_NUM(MAP_BIRTH_ISLAND_EXTERIOR) },
    // O resto no alto do farol de Olivine. O povo dela vive sob lampada
    // artificial desde que o mundo deles escureceu; esta aqui e enorme e so
    // existe para manter barco longe da pedra. Ela nao tem funcao nenhuma la.
    { SCHED_EVERY_DAY,                               SCHED_ANY_TIME,
      MAP_GROUP(MAP_OLIVINE_CITY_LIGHTHOUSE_TOP), MAP_NUM(MAP_OLIVINE_CITY_LIGHTHOUSE_TOP) },
};

// Os tres de Alola que vieram para o Mt. Ember. Sao as pessoas DESTE mundo,
// nao os fragmentos do Nexus (NEXUS_REGRAS R21): nao conhecem o jogador.
// Cada um tem um motivo ligado a montanha, e a agenda diz qual e:
//  - Guzma treina onde ninguem ve ele perder: de noite no cume, de dia na
//    encosta, e o resto do tempo emburrado na praia.
//  - Hau veio pela comida do spa: de dia la, de tarde na cidade, e o resto
//    do tempo andando pela Kindle Road.
//  - Olivia caca o rubi que deu nome ao Ruby Path: dia util la embaixo, toda
//    noite no spa, e o resto na cidade.
// Scripts e falas: data/scripts/mt_ember_residents.inc.

static const struct NpcScheduleSlot sGuzmaSchedule[] =
{
    { SCHED_EVERY_DAY, SCHED_DARK,     MAP_GROUP(MAP_MT_EMBER_SUMMIT),            MAP_NUM(MAP_MT_EMBER_SUMMIT)            },
    { SCHED_WEEKDAYS,  SCHED_DAYLIGHT, MAP_GROUP(MAP_MT_EMBER_EXTERIOR),          MAP_NUM(MAP_MT_EMBER_EXTERIOR)          },
    { SCHED_EVERY_DAY, SCHED_ANY_TIME, MAP_GROUP(MAP_ONE_ISLAND_TREASURE_BEACH),  MAP_NUM(MAP_ONE_ISLAND_TREASURE_BEACH)  },
};

static const struct NpcScheduleSlot sHauSchedule[] =
{
    { SCHED_EVERY_DAY, SCHED_DAYLIGHT, MAP_GROUP(MAP_ONE_ISLAND_KINDLE_ROAD_EMBER_SPA), MAP_NUM(MAP_ONE_ISLAND_KINDLE_ROAD_EMBER_SPA) },
    { SCHED_EVERY_DAY, SCHED_EVENING,  MAP_GROUP(MAP_ONE_ISLAND),                       MAP_NUM(MAP_ONE_ISLAND)                       },
    { SCHED_EVERY_DAY, SCHED_ANY_TIME, MAP_GROUP(MAP_ONE_ISLAND_KINDLE_ROAD),           MAP_NUM(MAP_ONE_ISLAND_KINDLE_ROAD)           },
};

static const struct NpcScheduleSlot sOliviaSchedule[] =
{
    { SCHED_WEEKDAYS,  SCHED_DAYLIGHT, MAP_GROUP(MAP_MT_EMBER_RUBY_PATH_B3F),           MAP_NUM(MAP_MT_EMBER_RUBY_PATH_B3F)           },
    { SCHED_EVERY_DAY, SCHED_DARK,     MAP_GROUP(MAP_ONE_ISLAND_KINDLE_ROAD_EMBER_SPA), MAP_NUM(MAP_ONE_ISLAND_KINDLE_ROAD_EMBER_SPA) },
    { SCHED_EVERY_DAY, SCHED_ANY_TIME, MAP_GROUP(MAP_ONE_ISLAND),                       MAP_NUM(MAP_ONE_ISLAND)                       },
};

static const struct NpcSchedule sNpcSchedules[SCHEDULED_NPC_COUNT] =
{
    [SCHEDULED_NPC_FLANNERY] = { sFlannerySchedule, ARRAY_COUNT(sFlannerySchedule) },
    [SCHEDULED_NPC_COLRESS]  = { sColressSchedule,  ARRAY_COUNT(sColressSchedule)  },
    [SCHEDULED_NPC_SOLIERA]  = { sSolieraSchedule,  ARRAY_COUNT(sSolieraSchedule)  },
    [SCHEDULED_NPC_GUZMA]    = { sGuzmaSchedule,    ARRAY_COUNT(sGuzmaSchedule)    },
    [SCHEDULED_NPC_HAU]      = { sHauSchedule,      ARRAY_COUNT(sHauSchedule)      },
    [SCHEDULED_NPC_OLIVIA]   = { sOliviaSchedule,   ARRAY_COUNT(sOliviaSchedule)   },
};
