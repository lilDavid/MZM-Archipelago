#ifndef METROID_DATA_H
#define METROID_DATA_H

#include "types.h"
#include "oam.h"
#include "macros.h"

extern const s16 sMetroidSpawningYMovement[65];

extern const s16 sMetroidSpawningXMovement[81];

extern const u32 sMetroidGfx[793];
extern const u16 sMetroidPal[80];
extern const u16 sMetroidPal_SamusGrabbed[80];

extern const u16 sMetroidOam_Moving_Frame10[OAM_DATA_SIZE(6)];

extern const struct FrameData sMetroidShellOam_Idle[3];
extern const struct FrameData sMetroidOam_Moving[17];
extern const struct FrameData sMetroidOam_SamusGrabbed[15];
extern const struct FrameData sMetroidOam_Spawning[3];

#endif /* METROID_DATA_H */
