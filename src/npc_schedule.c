#include "global.h"
#include "event_data.h"
#include "npc_schedule.h"
#include "rtc.h"
#include "constants/map_groups.h"
#include "constants/npc_schedule.h"
#include "constants/rtc.h"
#include "constants/vars.h"

// Quem decide se um personagem de agenda esta neste mapa agora.
//
// O script do mapa anfitriao chama assim, no ON_TRANSITION:
//
//     setvar VAR_0x8004, SCHEDULED_NPC_FLANNERY
//     special IsScheduledNpcHere
//     goto_if_eq VAR_RESULT, TRUE, <deixa aparecer>
//
// A ocultacao usa FLAG_TEMP_D, que zera a cada carregamento de mapa: como a
// resposta e recalculada toda entrada, nao ha estado para guardar e nenhuma
// flag persistente e gasta. E o mesmo truque do NPC de domingo do Goldenrod
// Dept. Store 5F.

#include "data/npc_schedule.h"

bool8 IsScheduledNpcHere(void)
{
    const struct NpcSchedule *schedule;
    u32 i, dayBit, timeBit;

    gSpecialVar_Result = FALSE;

    if (gSpecialVar_0x8004 >= SCHEDULED_NPC_COUNT)
        return FALSE;

    schedule = &sNpcSchedules[gSpecialVar_0x8004];
    if (schedule->slots == NULL || schedule->count == 0)
        return FALSE;

    // VarGet em vez de gLocalTime: o VAR_DAY_OF_WEEK e escrito por
    // UpdateTimeOfDay e e o mesmo numero que os scripts do Mt. Silver leem,
    // entao o dia nunca diverge entre os dois sistemas.
    dayBit = 1 << (VarGet(VAR_DAY_OF_WEEK) % 7);
    timeBit = 1 << GetTimeOfDay();

    for (i = 0; i < schedule->count; i++)
    {
        const struct NpcScheduleSlot *slot = &schedule->slots[i];

        if (!(slot->days & dayBit) || !(slot->times & timeBit))
            continue;

        // A primeira fatia que casa decide, inclusive quando o mapa nao e
        // este: a pessoa esta em outro lugar agora, e nao em dois.
        gSpecialVar_Result = (slot->mapGroup == gSaveBlock1Ptr->location.mapGroup
                           && slot->mapNum == gSaveBlock1Ptr->location.mapNum);
        return gSpecialVar_Result;
    }

    return FALSE;
}
