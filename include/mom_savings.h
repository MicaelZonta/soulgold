#ifndef GUARD_MOM_SAVINGS_H
#define GUARD_MOM_SAVINGS_H

#include "global.h"

#define MOM_RANDOM_THRESHOLD 2300
#define MOM_BERRY_QUANTITY 5
#define MOM_BERRY_COST 100
#define MOM_MAX_MONEY 999999

struct MomGiftSequential
{
    u16 itemId;
    u32 threshold;
    u16 cost;
    bool8 isDecoration;
};

void Mom_EnableSaving(bool8 enable);
bool8 Mom_IsSavingEnabled(void);
u32 Mom_GetBalance(void);
bool8 Mom_TryDepositMoney(u32 amount);
bool8 Mom_AutoDepositFromBattle(u32 amount);
bool8 Mom_TryWithdrawMoney(u32 amount);
bool8 Mom_CheckForGiftPurchase(u32 newBalance, u32 oldBalance, bool8 isAutomatic);
void Mom_EnsureInitialized(void);
void InitMomSavings(void);
bool8 Mom_TryTriggerGiftCall(void);

// Script entry points. SoulGold calls these with callnative (no specials.inc
// entry needed); results go to gSpecialVar_Result / gSpecialVar_0x8000.
struct ScriptContext;
void Special_MomEnableSaving(struct ScriptContext *ctx);
void Special_MomDisableSaving(struct ScriptContext *ctx);
void Special_MomGetBalance(struct ScriptContext *ctx);
void Special_MomDeposit(struct ScriptContext *ctx);
void Special_MomWithdraw(struct ScriptContext *ctx);
void Special_MomIsSavingEnabled(struct ScriptContext *ctx);
void Special_MomEnsureInitialized(struct ScriptContext *ctx);
void Special_MomOpenDepositInput(struct ScriptContext *ctx);
void Special_MomOpenWithdrawInput(struct ScriptContext *ctx);

#endif // GUARD_MOM_SAVINGS_H
