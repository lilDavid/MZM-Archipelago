#ifndef GUNSHIP_DATA_DATA_H
#define GUNSHIP_DATA_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sGunshipTakingOffYVelocity[153];

extern const s16 sGunshipFlyingYVelocity[22];

extern const u32 sGunshipGfx[1027];
extern const u16 sGunshipPal[48];
extern const u16 sGunshipFlashingPal[8 * 16];

extern const struct FrameData sGunshipOam_Idle[7];
extern const struct FrameData sGunshipOam_Refilling[7];

extern const struct FrameData sGunshipPartOam_EntranceFrontClosed[2];
extern const struct FrameData sGunshipPartOam_EntranceFrontOpening[5];
extern const struct FrameData sGunshipPartOam_EntranceFrontOpened[7];
extern const struct FrameData sGunshipPartOam_EntranceFrontClosing[6];
extern const struct FrameData sGunshipPartOam_EntranceBackClosed[2];
extern const struct FrameData sGunshipPartOam_EntranceBackOpening[9];
extern const struct FrameData sGunshipPartOam_EntranceBackOpened[7];
extern const struct FrameData sGunshipPartOam_EntranceBackClosing[9];

extern const struct FrameData sGunshipPartOam_Platform[5];

extern const struct FrameData sGunshipOam_Flying[7];

extern const struct FrameData sGunshipPartOam_FlamesHorizontal[4];
extern const struct FrameData sGunshipPartOam_FlamesVertical[4];

#endif /* GUNSHIP_DATA_DATA_H */
