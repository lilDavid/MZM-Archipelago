#ifndef ZEELA_DATA_H
#define ZEELA_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sZeelaEyesFallingFromUpSpeed[16];

extern const s16 sZeelaEyesFallingFromBottomSpeed[12];

extern const u32 sZeelaGfx[578];
extern const u16 sZeelaPal[32];

extern const struct FrameData sZeelaOam_OnGround[5];
extern const struct FrameData sZeelaOam_TurningEdgeLeft[4];
extern const struct FrameData sZeelaOam_TurningEdgeRight[4];
extern const struct FrameData sZeelaOam_OnWall[5];
extern const struct FrameData sZeelaOam_TurningCornerRight[4];
extern const struct FrameData sZeelaOam_TurningCornerLeft[4];
extern const struct FrameData sZeelaOam_WalkingOnSlope[5];
extern const struct FrameData sZeelaOam_FallingOnGround[9];
extern const struct FrameData sZeelaOam_FallingOnWall[9];
extern const struct FrameData sZeelaEyesOam_Idle[2];
extern const struct FrameData sZeelaEyesOam_Spinning_Unused[5];
extern const struct FrameData sZeelaEyesOam_Exploding[4];

#endif /* ZEELA_DATA_H */
