#ifndef ZIPLINE_DATA_H
#define ZIPLINE_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sZiplineGfx[264];
extern const u16 sZiplinePal[16];

extern const struct FrameData sZiplineOam_OffIdle[2];
extern const struct FrameData sZiplineOam_OffGrabbingSamus[4];
extern const struct FrameData sZiplineOam_OffSamusGrabbed[2];
extern const struct FrameData sZiplineOam_OffReleasingSamus[4];
extern const struct FrameData sZiplineOam_OnIdle[7];
extern const struct FrameData sZiplineOam_OnGrabbingSamus[4];
extern const struct FrameData sZiplineOam_OnSamusGrabbed[7];
extern const struct FrameData sZiplineOam_OnReleasingSamus[4];

extern const struct FrameData sZiplineButtonOam_OffIdle[2];
extern const struct FrameData sZiplineButtonOam_OnIdle[7];
extern const struct FrameData sZiplineButtonOam_Active[7];

#endif /* ZIPLINE_DATA_H */
