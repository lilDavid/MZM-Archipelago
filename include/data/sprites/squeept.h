#ifndef SQUEEPT_DATA_H
#define SQUEEPT_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sSqueeptRisingMovement[65];
extern const s16 sSqueeptFallingMovement[16];

extern const u32 sSqueeptGfx[263];
extern const u16 sSqueeptPal[16];

extern const struct FrameData sSqueeptOam_TurningAround[6];
extern const struct FrameData sSqueeptOam_TurningAround_Unused[6];
extern const struct FrameData sSqueeptOam_GoingDown[3];
extern const struct FrameData sSqueeptOam_GoingUp[8];

#endif /* SQUEEPT_DATA_H */
