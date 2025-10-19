#ifndef MESSAGE_BANNER_DATA_H
#define MESSAGE_BANNER_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sMessageBannerGfx[139];
extern const u16 sMessageBannerPal[32];

extern const struct FrameData sSaveYesNoCursorOam_Idle[5];

extern const struct FrameData sMessageBannerOam_TwoLinesSpawn[11];

extern const struct FrameData sMessageBannerOam_TwoLinesRemoving[11];

extern const struct FrameData sMessageBannerOam_TwoLinesStatic[2];

extern const struct FrameData sMessageBannerOam_OneLineSpawn[9];

extern const struct FrameData sMessageBannerOam_OneLineRemoving[9];

extern const struct FrameData sMessageBannerOam_OneLineStatic[2];

#endif /* MESSAGE_BANNER_DATA_H */
