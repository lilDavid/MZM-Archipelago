#ifndef SPACE_PIRATE_DATA_H
#define SPACE_PIRATE_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sSpacePirateWallJumpingVelocity[8];

extern const s16 sSpacePirate_2e1030[11];

extern const s16 sSpacePirateJumpingVelocity[10];

extern const s16 sSpacePirate_2e105a[11];

extern const s16 sSpacePirate_2e1070[12];

extern const u32 sSpacePirateGfx[810];
extern const u16 sSpacePiratePal[48];

extern const struct FrameData sSpacePirateOam_Crouched[5];
extern const struct FrameData sSpacePirateOam_Walking[9];
extern const struct FrameData sSpacePirateOam_ChargingLaserForward[8];

extern const struct FrameData sSpacePirateLaserOam_Forward[4];

extern const struct FrameData sSpacePirateOam_TurningAroundFirstPart[5];
extern const struct FrameData sSpacePirateOam_TurningAroundSecondPart[5];
extern const struct FrameData sSpacePirateOam_StandingMotionless_Unused[2];
extern const struct FrameData sSpacePirateOam_ShootingForward[5];
extern const struct FrameData sSpacePirateOam_Jumping[8];
extern const struct FrameData sSpacePirateOam_ChargingLaserDiagonallyDown[8];
extern const struct FrameData sSpacePirateOam_Falling[2];
extern const struct FrameData sSpacePirateOam_Landing[5];
extern const struct FrameData sSpacePirateOam_ShootingDiagonallyDown[5];
extern const struct FrameData sSpacePirateOam_LookingUpwards_Unused[5];
extern const struct FrameData sSpacePirateOam_ChargingLaserDiagonallyUp[8];
extern const struct FrameData sSpacePirateOam_ShootingDiagonallyUp[5];
extern const struct FrameData sSpacePirateOam_ClimbingUp[9];
extern const struct FrameData sSpacePirateOam_ClimbingDown[9];
extern const struct FrameData sSpacePirateOam_StartingToCrawl[6];
extern const struct FrameData sSpacePirateOam_Crawling[9];
extern const struct FrameData sSpacePirateOam_StandingUp[6];
extern const struct FrameData sSpacePirateOam_TurningAroundWhileCrawlingFirstPart[6];
extern const struct FrameData sSpacePirateOam_TurningAroundWhileCrawlingSecondPart[6];
extern const struct FrameData sSpacePirateOam_CrawlingStopped[5];
extern const struct FrameData sSpacePirateOam_TurningToAimWhileClimbing[4];
extern const struct FrameData sSpacePirateOam_AimingWhileClimbing[5];
extern const struct FrameData sSpacePirateOam_ClimbingChargingLaserForward[3];
extern const struct FrameData sSpacePirateOam_ClimbingShootingForward[5];
extern const struct FrameData sSpacePirateOam_ClimbingRetractingAim[5];
extern const struct FrameData sSpacePirateOam_LaunchingFromWall[4];
extern const struct FrameData sSpacePirateOam_JumpingFromWall[4];

extern const struct FrameData sSpacePirateLaserOam_Diagonal[4];

extern const struct FrameData sSpacePirateOam_Standing[5];
extern const struct FrameData sSpacePirateOam_StandingAlerted[5];
extern const struct FrameData sSpacePirateOam_OnWallIdle_Unused[5];

extern const struct FrameData sSpacePirateLaserOam_Exploding[8];

extern const struct FrameData sSpacePirateOam_LookingAtCamera_Unused[5];

extern const struct FrameData sSpacePirateCarryingPowerBombOam[9];

#endif /* SPACE_PIRATE_DATA_H */
