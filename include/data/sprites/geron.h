#ifndef GERON_DATA_H
#define GERON_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sGeronGfx[711];
extern const u16 sGeronPal[48];

extern const struct FrameData sGeronOam_Idle[11];
extern const struct FrameData sGeronOam_Destroyed[2];
extern const struct FrameData sGeronOam_GettingDestroyed[32];
extern const struct FrameData sGeronOam_Shaking[37];

#endif /* GERON_DATA_H */
