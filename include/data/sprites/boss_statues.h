#ifndef BOSS_STATUES_DATA_H
#define BOSS_STATUES_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sBossStatuesGfx[2388];
extern const u16 sBossStatuesPal[128];

extern const struct FrameData sKraidStatueOam_Idle[2];
extern const struct FrameData sKraidStatueOam_Activating[13];
extern const struct FrameData sKraidStatueOam_Activated[7];
extern const struct FrameData sKraidStatueOam_Opening[43];
extern const struct FrameData sKraidStatueOam_Opened[2];

extern const struct FrameData sRidleyStatueOam_Idle[2];
extern const struct FrameData sRidleyStatueOam_Activating[13];
extern const struct FrameData sRidleyStatueOam_Activated[7];
extern const struct FrameData sRidleyStatueOam_Opening[43];
extern const struct FrameData sRidleyStatueOam_Opened[2];

#endif /* BOSS_STATUES_DATA_H */
