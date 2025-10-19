#ifndef GEEGA_DATA_H
#define GEEGA_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sGeegaGfx[153];
extern const u16 sGeegaPal[16];
extern const u32 sGeegaWhiteGfx[153];
extern const u16 sGeegaWhitePal[16];

extern const struct FrameData sGeegaOam_Idle[5];
extern const struct FrameData sGeegaOam_Moving[9];

#endif /* GEEGA_DATA_H */
