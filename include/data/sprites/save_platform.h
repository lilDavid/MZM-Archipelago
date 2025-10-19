#ifndef SAVE_PLATFORM_DATA_H
#define SAVE_PLATFORM_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sSavePlatformGfx[603];
extern const u16 sSavePlatformPal[64];

extern const struct FrameData sSavePlatformOam_Idle[7];
extern const struct FrameData sSavePlatformOam_Opening[4];
extern const struct FrameData sSavePlatformOam_Opened[7];
extern const struct FrameData sSavePlatformOam_Saving[7];
extern const struct FrameData sSavePlatformOam_OpenedOff[2];
extern const struct FrameData sSavePlatformOam_Closing[4];
extern const struct FrameData sSavePlatformOam_IdleOff[2];

extern const struct FrameData sSavePlatformPartOam_TopIdle[2];
extern const struct FrameData sSavePlatformPartOam_TopExtending[6];
extern const struct FrameData sSavePlatformPartOam_TopExtended[2];
extern const struct FrameData sSavePlatformPartOam_TopRetracting[6];
extern const struct FrameData sSavePlatformPartOam_TubeSpawning[39];
extern const struct FrameData sSavePlatformPartOam_TubeShadow[13];
extern const struct FrameData sSavePlatformPartOam_TubeIdle[3];
extern const struct FrameData sSavePlatformPartOam_Tube_Unused[5];
extern const struct FrameData sSavePlatformPartOam_TubeDespawning[17];
extern const struct FrameData sSavePlatformPartOam_Ray[9];

#endif /* #define SAVE_PLATFORM_DATA_H */
