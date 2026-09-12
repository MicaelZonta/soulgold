#include "global.h"
#include "data.h"
#include "event_data.h"
#include "script.h"

enum DifficultyLevel GetCurrentDifficultyLevel(void)
{
    // The sole trainer dataset is stored in the default slot for save and data
    // compatibility. Its parties were promoted from the former Hard dataset.
    return DIFFICULTY_NORMAL;
}

void SetCurrentDifficultyLevel(enum DifficultyLevel desiredDifficulty)
{
    // Keep this entry point for scripts and old saves, but do not persist or
    // select a difficulty. The serialized bit remains reserved in SaveBlock2.
    (void)desiredDifficulty;
}

enum DifficultyLevel GetBattlePartnerDifficultyLevel(u16 partnerId)
{
    if (partnerId > TRAINER_PARTNER(PARTNER_NONE))
        partnerId -= TRAINER_PARTNER(PARTNER_NONE);

    return DIFFICULTY_NORMAL;
}

enum DifficultyLevel GetTrainerDifficultyLevel(u16 trainerId)
{
    (void)trainerId;
    return DIFFICULTY_NORMAL;
}

void Script_IncreaseDifficulty(void)
{
    // Legacy script command retained as a no-op for compiled map scripts.
}

void Script_DecreaseDifficulty(void)
{
    // Legacy script command retained as a no-op for compiled map scripts.
}

void Script_GetDifficulty(void)
{
    gSpecialVar_Result = GetCurrentDifficultyLevel();
}

void Script_SetDifficulty(struct ScriptContext *ctx)
{
    (void)ctx;
}
