#ifndef PARASITE_DATA_H
#define PARASITE_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sParasiteGfx[309];
extern const u16 sParasitePal[16];

extern const struct FrameData sParasiteOam_Idle[7];

extern const struct FrameData sParasiteOam_LandingAfterFalling[5];

extern const struct FrameData sParasiteOam_Landing[4];

extern const struct FrameData sParasiteOam_Tumbling[5];

extern const struct FrameData sParasiteOam_TurningBackOnFeet[8];

extern const struct FrameData sParasiteOam_TurningAround[2];

extern const struct FrameData sParasiteOam_JumpingUp_Unused[7];

extern const struct FrameData sParasiteOam_JumpingDown_Unused[7];

extern const struct FrameData sParasiteOam_JumpingUp[3];

extern const struct FrameData sParasiteOam_Attached_Unused[9];

extern const struct FrameData sParasiteOam_Attached[9];

extern const struct FrameData sParasiteOam_Expelled[9];

extern const struct FrameData sParasiteOam_Dying_Unused[5];

extern const struct FrameData sParasiteOam_Dying[11];

#endif /* PARASITE_DATA_H */
