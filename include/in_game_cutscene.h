#ifndef IN_GAME_CUTSCENE_H
#define IN_GAME_CUTSCENE_H

#include "types.h"

#include "constants/in_game_cutscene.h"

u32 InGameCutsceneSamusCloseUp(InGameCutsceneScene cutsceneNumber, InGameCutsceneScene cutsceneNumberNoFlag);
void unk_5fd58(void);

u32 InGameCutsceneUpgradingSuit(InGameCutsceneScene cutsceneNumber, InGameCutsceneScene cutsceneNumberNoFlag);
u16 InGameCutsceneCalculateSuitFlashOffset(u8 intensity, u8 start, u8 end);

void MakeBackgroundFlash(BackgroundFlash type);

void InGameCutsceneStart(InGameCutsceneScene number);
void InGameCutsceneProcess(void);
void InGameCutsceneInit(void);
void InGameCutsceneCheckPlayOnTransition(void);

boolu32 InGameCutsceneTryQueue(InGameCutsceneScene cutscene);
void InGameCutsceneCheckStartQueued(void);

void UpdateAnimatedPaletteAfterTransitionOrReload(void);
u32 InGameCutsceneCheckFlag(u8 setting, u8 param_2);

#endif /* IN_GAME_CUTSCENE_H */
