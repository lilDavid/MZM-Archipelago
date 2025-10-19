#ifndef POLYP_DATA_H
#define POLYP_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sPolypProjectileYVelocity[44];

extern const u32 sPolypGfx[241];
extern const u16 sPolypPal[16];

extern const struct FrameData sPolypOam_Idle[5];

extern const struct FrameData sPolypOam_Warning[5];

extern const struct FrameData sPolypOam_Spitting[2];

extern const struct FrameData sPolypOam_AfterSpitting[4];

extern const struct FrameData sPolypOam_Retracting[3];

extern const struct FrameData sPolypProjectileOam_Right[5];

extern const struct FrameData sPolypProjectileOam_Left[5];

extern const struct FrameData sPolypProjectileOam_Exploding[5];

#endif /* POLYP_DATA_H */
