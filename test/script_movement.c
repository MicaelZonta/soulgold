#include "global.h"
#include "test/test.h"
#include "event_object_movement.h"
#include "load_save.h"
#include "script_movement.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_object_movement.h"

static const u8 sStepEndMovement[] = { MOVEMENT_ACTION_STEP_END };

static void SetUpObjectEvents(void)
{
    u32 i;

    memset(gObjectEvents, 0, sizeof(gObjectEvents));
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        gObjectEvents[i].active = TRUE;
        gObjectEvents[i].localId = i + 1;
        gObjectEvents[i].spriteId = MAX_SPRITES; // dummy sprite slot
    }
}

TEST("waitmovement finishes with more than 16 objects moving at once")
{
    u32 i;

    ASSUME(OBJECT_EVENTS_COUNT > 16);
    ResetTasks();
    SetUpObjectEvents();

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
        EXPECT_EQ(ScriptMovement_StartObjectMovementScript(i + 1, 0, 0, sStepEndMovement), FALSE);

    EXPECT(!ScriptMovement_IsAllObjectMovementFinished());
    RunTasks();

    EXPECT(ScriptMovement_IsAllObjectMovementFinished());
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        EXPECT(ScriptMovement_IsObjectMovementFinished(i + 1, 0, 0));
        EXPECT(gObjectEvents[i].frozen);
    }

    ScriptMovement_UnfreezeObjectEvents();
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
        EXPECT(!gObjectEvents[i].frozen);
}

TEST("Object events past the legacy 16 slots survive save and load")
{
    u32 i;

    ASSUME(OBJECT_EVENTS_COUNT > OBJECT_EVENTS_SAVE_LEGACY_COUNT);
    SetUpObjectEvents();
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        gObjectEvents[i].graphicsId = 0x100 + i;
        gObjectEvents[i].currentCoords.x = i * 3;
        gObjectEvents[i].currentCoords.y = i * 5;
    }

    SaveObjectEvents();
    memset(gObjectEvents, 0, sizeof(gObjectEvents));
    LoadObjectEvents();

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        EXPECT(gObjectEvents[i].active);
        EXPECT_EQ(gObjectEvents[i].localId, i + 1);
        EXPECT_EQ(gObjectEvents[i].graphicsId, 0x100 + i);
        EXPECT_EQ(gObjectEvents[i].currentCoords.x, i * 3);
        EXPECT_EQ(gObjectEvents[i].currentCoords.y, i * 5);
    }
}
