#ifndef SAVE_PLATFORM_CHOZODIA_DATA_H
#define SAVE_PLATFORM_CHOZODIA_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sSavePlatformChozodiaGfx[552];
extern const u16 sSavePlatformChozodiaPal[64];

extern const struct FrameData sSavePlatformChozodiaOam_Idle[7];
extern const struct FrameData sSavePlatformChozodiaOam_Opening[7];
extern const struct FrameData sSavePlatformChozodiaOam_Opened[7];
extern const struct FrameData sSavePlatformChozodiaOam_Saving[7];
extern const struct FrameData sSavePlatformChozodiaOam_IdleOff[2];
extern const struct FrameData sSavePlatformChozodiaOam_Closing[7];
extern const struct FrameData sSavePlatformChozodiaOam_OpenedOff[2];

extern const struct FrameData sSavePlatformChozodiaPartOam_TopIdle[2];
extern const struct FrameData sSavePlatformChozodiaPartOam_TopExtending[6];
extern const struct FrameData sSavePlatformChozodiaPartOam_TopExtended[2];
extern const struct FrameData sSavePlatformChozodiaPartOam_TopRetracting[6];
extern const struct FrameData sSavePlatformChozodiaPartOam_TubeSpawning[39];
extern const struct FrameData sSavePlatformChozodiaPartOam_TubeShadow[13];
extern const struct FrameData sSavePlatformChozodiaPartOam_TubeIdle[3];
extern const struct FrameData sSavePlatformChozodiaPartOam_Tube_Unused[5];
extern const struct FrameData sSavePlatformChozodiaPartOam_TubeDespawning[17];
extern const struct FrameData sSavePlatformChozodiaPartOam_Ray[9];
extern const struct FrameData sSavePlatformChozodiaPartOam_RefillLight[9];

#endif /* SAVE_PLATFORM_CHOZODIA_DATA_H */
