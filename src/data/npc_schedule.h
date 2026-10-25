// A agenda de cada personagem que roda pelo mundo.
//
// Regras da tabela:
//  - As fatias de um personagem sao lidas na ordem; a primeira que casar com o
//    dia E a hora ganha. Entao a ultima fatia pode ser o "resto da semana".
//  - Um personagem nao precisa estar em lugar nenhum: se nada casar, ele some
//    de todos os mapas naquele horario, e isso e legitimo.
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

// Os dois que ficaram na Birth Island depois da historia. Os dois sao do
// Nexus e nao existiam em lugar nenhum do mundo ate agora.
//
// Sabado os dois estao la ao mesmo tempo, de proposito: e o unico dia em que
// o jogador ve os dois discordando sobre o que fazer com a cratera.

static const struct NpcScheduleSlot sColressSchedule[] =
{
    { SCHED_MON | SCHED_WED | SCHED_FRI | SCHED_SAT, SCHED_ANY_TIME,
      MAP_GROUP(MAP_BIRTH_ISLAND_EXTERIOR), MAP_NUM(MAP_BIRTH_ISLAND_EXTERIOR) },
};

static const struct NpcScheduleSlot sSolieraSchedule[] =
{
    { SCHED_TUE | SCHED_THU | SCHED_SAT, SCHED_ANY_TIME,
      MAP_GROUP(MAP_BIRTH_ISLAND_EXTERIOR), MAP_NUM(MAP_BIRTH_ISLAND_EXTERIOR) },
};

static const struct NpcSchedule sNpcSchedules[SCHEDULED_NPC_COUNT] =
{
    [SCHEDULED_NPC_FLANNERY] = { sFlannerySchedule, ARRAY_COUNT(sFlannerySchedule) },
    [SCHEDULED_NPC_COLRESS]  = { sColressSchedule,  ARRAY_COUNT(sColressSchedule)  },
    [SCHEDULED_NPC_SOLIERA]  = { sSolieraSchedule,  ARRAY_COUNT(sSolieraSchedule)  },
};
