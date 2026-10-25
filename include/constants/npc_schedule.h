#ifndef GUARD_CONSTANTS_NPC_SCHEDULE_H
#define GUARD_CONSTANTS_NPC_SCHEDULE_H

// Agenda de NPC: personagem que nao mora num mapa so, e sim aparece em lugares
// diferentes conforme o dia da semana e a hora. A tabela esta em
// src/data/npc_schedule.h e quem pergunta e o special IsScheduledNpcHere.
//
// O padrao de revezamento por dia ja existia no repo (Red e rival no topo do
// Mt. Silver, .claude/merge_hns/summit_red_rival.md) escrito a mao em cada
// mapa. Isto generaliza: um personagem, varios mapas, e a hora tambem conta.

// #define, nao enum: o setvar do script e montado pelo assembler, que so
// enxerga o que o cpp ja substituiu.
#define SCHEDULED_NPC_FLANNERY  0
#define SCHEDULED_NPC_COLRESS   1
#define SCHEDULED_NPC_SOLIERA   2
#define SCHEDULED_NPC_COUNT     3

// VAR_DAY_OF_WEEK e 0 = domingo (src/overworld.c, UpdateTimeOfDay).
#define SCHED_SUN   (1 << 0)
#define SCHED_MON   (1 << 1)
#define SCHED_TUE   (1 << 2)
#define SCHED_WED   (1 << 3)
#define SCHED_THU   (1 << 4)
#define SCHED_FRI   (1 << 5)
#define SCHED_SAT   (1 << 6)

#define SCHED_WEEKDAYS  (SCHED_MON | SCHED_TUE | SCHED_WED | SCHED_THU | SCHED_FRI)
#define SCHED_WEEKEND   (SCHED_SAT | SCHED_SUN)
#define SCHED_EVERY_DAY (SCHED_WEEKDAYS | SCHED_WEEKEND)

// Espelha enum TimeOfDay (include/constants/rtc.h).
#define SCHED_MORNING (1 << TIME_MORNING)
#define SCHED_DAY     (1 << TIME_DAY)
#define SCHED_EVENING (1 << TIME_EVENING)
#define SCHED_NIGHT   (1 << TIME_NIGHT)

#define SCHED_DAYLIGHT  (SCHED_MORNING | SCHED_DAY)
#define SCHED_DARK      (SCHED_EVENING | SCHED_NIGHT)
#define SCHED_ANY_TIME  (SCHED_DAYLIGHT | SCHED_DARK)

#endif // GUARD_CONSTANTS_NPC_SCHEDULE_H
