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

static const struct NpcSchedule sNpcSchedules[SCHEDULED_NPC_COUNT] =
{
    [SCHEDULED_NPC_FLANNERY] = { sFlannerySchedule, ARRAY_COUNT(sFlannerySchedule) },
};
