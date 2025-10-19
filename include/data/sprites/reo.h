#ifndef REO_DATA_H
#define REO_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sReoIdleYMovement[65];

extern const s16 sReoIdleXMovement[81];

extern const u32 sReoGreenWingsGfx[277];
extern const u16 sReoGreenWingsPal[16];
extern const u32 sReoPurpleWingsGfx[277];
extern const u16 sReoPurpleWingsPal[16];

extern const struct FrameData sReoOam_Unused1[5];
extern const struct FrameData sReoOam_Idle[5];
extern const struct FrameData sReoOam_Idle_Unused[9];
extern const struct FrameData sReoOam_Moving[13];
extern const struct FrameData sReoOam_Unused2[21];
extern const struct FrameData sReoOam_Unused3[9];
extern const struct FrameData sReoOam_Moving_Unused[5];

#endif /* REO_DATA_H */
