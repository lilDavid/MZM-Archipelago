#ifndef HOLTZ_DATA_H
#define HOLTZ_DATA_H

#include "types.h"
#include "macros.h"
#include "oam.h"

extern const s16 sHoltzIdleYVelocity[65];

extern const u32 sHoltzGfx[200];
extern const u16 sHoltzPal[16];

extern const struct FrameData sHoltzOam_Idle[5];
extern const struct FrameData sHoltzOam_Warning[10];
extern const struct FrameData sHoltzOam_GoingDown[3];
extern const struct FrameData sHoltzOam_IdleAware[4];
extern const struct FrameData sHoltzOam_GoingUp[8];
extern const struct FrameData sHoltzOam_BonkingOnCeiling[10];

#endif /* HOLTZ_DATA_H */
