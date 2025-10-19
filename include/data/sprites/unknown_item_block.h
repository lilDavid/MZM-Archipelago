#ifndef UNKNOWN_ITEM_BLOCK_DATA_H
#define UNKNOWN_ITEM_BLOCK_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sPlasmaBeamBlockGfx[306];
extern const u16 sPlasmaBeamBlockPal[16];
extern const u32 sGravityBlockGfx[303];
extern const u16 sGravityBlockPal[16];
extern const u32 sSpaceJumpBlockGfx[297];
extern const u16 sSpaceJumpBlockPal[16];

extern const struct FrameData sUnknownItemBlockOam_Idle[2];
extern const struct FrameData sUnknownItemBlockOam_Activated[7];
extern const struct FrameData sUnknownItemBlockOam_Exploding[11];
extern const struct FrameData sUnknownItemBlockLightOam_Idle[3];

#endif /* UNKNOWN_ITEM_BLOCK_DATA_H */
