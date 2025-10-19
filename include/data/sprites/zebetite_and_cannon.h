#ifndef ZEBETITE_AND_CANNON_DATA_H
#define ZEBETITE_AND_CANNON_DATA_H

#include "types.h"
#include "macros.h"
#include "oam.h"

extern const u32 sRinkaZebetiteAndCannonGfx[476];
extern const u16 sRinkaZebetiteAndCannonPal[32];

extern const struct FrameData sRinkaMotherBrainOam_Spawning[16];
extern const struct FrameData sRinkaMotherBrainOam_Moving[5];

extern const struct FrameData sZebetiteOam_Phase1[7];
extern const struct FrameData sZebetiteOam_Phase2[7];
extern const struct FrameData sZebetiteOam_Phase4[7];
extern const struct FrameData sZebetiteOam_Phase6[7];

extern const struct FrameData sCannonOam_AimingLeft[2];
extern const struct FrameData sCannonOam_ShootingLeft[4];
extern const struct FrameData sCannonOam_LeftToDownLeftTransition[2];
extern const struct FrameData sCannonOam_AimingDownLeft[2];
extern const struct FrameData sCannonOam_ShootingDownLeft[4];
extern const struct FrameData sCannonOam_DownLeftToDownTransition[2];
extern const struct FrameData sCannonOam_AimingDown[2];
extern const struct FrameData sCannonOam_ShootingDown[4];
extern const struct FrameData sCannonOam_DownToDownRightTransition[2];
extern const struct FrameData sCannonOam_AimingDownRight[2];
extern const struct FrameData sCannonOam_ShootingDownRight[4];
extern const struct FrameData sCannonOam_DownRightToRightTransition[2];
extern const struct FrameData sCannonOam_AimingRight[2];
extern const struct FrameData sCannonOam_ShootingRight[4];
extern const struct FrameData sCannonBulletOam_Left[3];
extern const struct FrameData sCannonBulletOam_DownLeft[3];
extern const struct FrameData sCannonBulletOam_Down[3];
extern const struct FrameData sCannonBulletOam_DownRight[3];
extern const struct FrameData sCannonBulletOam_Right[3];

extern const struct FrameData sMotherBrainBlockOam[5];

#endif /* ZEBETITE_AND_CANNON_DATA_H */
