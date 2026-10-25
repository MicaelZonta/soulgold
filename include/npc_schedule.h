#ifndef GUARD_NPC_SCHEDULE_H
#define GUARD_NPC_SCHEDULE_H

struct NpcScheduleSlot
{
    u8 days;        // mascara SCHED_SUN..SCHED_SAT
    u8 times;       // mascara SCHED_MORNING..SCHED_NIGHT
    u8 mapGroup;
    u8 mapNum;
};

struct NpcSchedule
{
    const struct NpcScheduleSlot *slots;
    u8 count;
};

bool8 IsScheduledNpcHere(void);
u16 GetTimeOfDayForScript(void);

#endif // GUARD_NPC_SCHEDULE_H
