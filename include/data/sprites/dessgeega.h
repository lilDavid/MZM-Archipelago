#ifndef DESSGEEGA_DATA_H
#define DESSGEEGA_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sDessgeegaHighJumpYVelocity[10];

extern const s16 sDessgeegaLowJumpYVelocity[10];

extern const u32 sDessgeegaGfx[270];
extern const u16 sDessgeegaPal[16];

extern const struct FrameData sDessGeegaOam_Idle[5];
extern const struct FrameData sDessGeegaOam_Screaming[12];
extern const struct FrameData sDessGeegaOam_JumpWarning[4];
extern const struct FrameData sDessGeegaOam_Jumping[3];
extern const struct FrameData sDessGeegaOam_Landing[5];

#endif /* DESSGEEGA_DATA_H */
