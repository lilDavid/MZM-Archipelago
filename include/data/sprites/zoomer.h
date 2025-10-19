#ifndef ZOOMER_DATA_H
#define ZOOMER_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sZoomerGfx[379];
extern const u16 sZoomerPal[32];

extern const struct FrameData sZoomerOam_Falling[5];
extern const struct FrameData sZoomerOam_OnGround[5];
extern const struct FrameData sZoomerOam_TurningEdgeLeft[4];
extern const struct FrameData sZoomerOam_TurningEdgeRight[4];
extern const struct FrameData sZoomerOam_OnWall[5];
extern const struct FrameData sZoomerOam_TurningCornerRight[4];
extern const struct FrameData sZoomerOam_TurningCornerLeft[4];
extern const struct FrameData sZoomerOam_WalkingOnLeftSlope[5];
extern const struct FrameData sZoomerOam_WalkingOnRightSlope[5];

#endif /* ZOOMER_DATA_H */
