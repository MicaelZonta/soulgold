#ifndef GUARD_BERRY_H
#define GUARD_BERRY_H

void SetEnigmaBerry(u8 *src);
bool32 IsEnigmaBerryValid(void);
const struct Berry *GetBerryInfo(u8 berry);
struct BerryTree *GetBerryTreeInfo(u8 id);
bool32 ObjectEventInteractionWaterBerryTree(void);
bool32 WaterBerryTreeById(u8 id);
void BerryTree_UpdateSoilTile(u8 treeId, s16 x, s16 y);
bool32 GetBerryRecipe(u16 itemId, u16 *parent1, u16 *parent2);
bool8 IsPlayerFacingEmptyBerryTreePatch(void);
bool8 TryToWaterBerryTree(void);
void ClearBerryTrees(void);
void BerryTreeTimeUpdate(s32 minutes);
void PlantBerryTree(u8 id, u8 berry, u8 stage, bool8 allowGrowth);
void RemoveBerryTree(u8 id);
u8 GetBerryTypeByBerryTreeId(u8 id);
u8 GetStageByBerryTreeId(u8 id);
u8 ItemIdToBerryType(enum Item item);
enum Item BerryTypeToItemId(u16 berry);
void GetBerryNameByBerryType(u8 berry, u8 *string);
void Bag_ChooseBerry(void);
void Bag_ChooseMulch(void);
void ObjectEventInteractionGetBerryTreeData(void);
void ObjectEventInteractionPlantBerryTree(void);
void ObjectEventInteractionPickBerryTree(void);
void ObjectEventInteractionRemoveBerryTree(void);
void ObjectEventInteractionApplyMulch(void);
bool8 PlayerHasBerries(void);
void SetBerryTreesSeen(void);
bool32 BerryTreeGrow(struct BerryTree *tree);

extern const struct Berry gBerries[];

struct BerryCrushBerryData {
    u8 difficulty; // The number of A presses required to crush it
    u16 powder;
};

extern const struct BerryCrushBerryData gBerryCrush_BerryData[];

#endif // GUARD_BERRY_H
