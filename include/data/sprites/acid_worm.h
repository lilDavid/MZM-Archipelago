#ifndef ACID_WORM_DATA_H
#define ACID_WORM_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sAcidWormSpitCloseYVelocity[16];

extern const s16 sAcidWormSpitFarYVelocity[26];

extern const s16 sAcidWormSpitMiddleYVelocity[20];

extern const s16 sAcidWormSwingingMovement[33];

extern const s16 sAcidWormHeadRandomXVelocity[45];

extern const u32 sAcidWormGfx[1000];
extern const u16 sAcidWormPal[64];

extern const struct FrameData sAcidWormOam_Idle[5];
extern const struct FrameData sAcidWormOam_Moving[3];
extern const struct FrameData sAcidWormOam_Spitting[15];
extern const struct FrameData sAcidWormOam_MouthClosed[5];

extern const struct FrameData sAcidWormPartOam_AroundMouth[2];
extern const struct FrameData sAcidWormPartOam_WeakPoint[9];
extern const struct FrameData sAcidWormPartOam_Unused[5];
extern const struct FrameData sAcidWormPartOam_BelowWeakPoint[2];
extern const struct FrameData sAcidWormPartOam_AboveSegments[2];
extern const struct FrameData sAcidWormPartOam_Segment[2];
extern const struct FrameData sAcidWormPartOam_Unused2[5];

extern const struct FrameData sAcidWormSpitOam_Moving[4];
extern const struct FrameData sAcidWormSpitOam_Exploding[6];

extern const struct FrameData sAcidWormOam_Warning[14];
extern const struct FrameData sAcidWormOam_SpawnOnTop[24];

#endif /* ACID_WORM_DATA_H */
