#ifndef GERUTA_DATA_H
#define GERUTA_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sGerutaRedGfx[321];
extern const u16 sGerutaRedPal[16];
extern const u32 sGerutaGreenGfx[308];
extern const u16 sGerutaGreenPal[16];

extern const struct FrameData sGerutaOam_Idle[3];
extern const struct FrameData sGerutaOam_Warning[4];
extern const struct FrameData sGerutaOam_Launching[5];
extern const struct FrameData sGerutaOam_GoingDown[5];
extern const struct FrameData sGerutaOam_Bouncing[3];
extern const struct FrameData sGerutaOam_GoingUp[5];
extern const struct FrameData sGerutaOam_BouncingOnCeiling[3];

#endif /* GERUTA_DATA_H */
