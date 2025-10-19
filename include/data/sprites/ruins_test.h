#ifndef RUINS_TEST_DATA_H
#define RUINS_TEST_DATA_H

#include "types.h"
#include "macros.h"
#include "oam.h"

extern const u32 sRuinsTestGfx[1951];
extern const u32 sRuinsTestGfx_SamusReflectionTurningRightTop[96];
extern const u32 sRuinsTestGfx_SamusReflectionTurningRightBottom[64];
extern const u32 sRuinsTestGfx_SamusReflectionTurningLeftTop[96];
extern const u32 sRuinsTestGfx_SamusReflectionTurningLeftBottom[64];
extern const u32 sRuinsTestGfx_SamusReflectionFullSuitTop[96];
extern const u32 sRuinsTestGfx_SamusReflectionFullSuitBottom[64];
extern const u32 sRuinsTestGfx_SamusReflectionSuitlessTop[96];
extern const u32 sRuinsTestGfx_SamusReflectionSuitlessBottom[64];
extern const u16 sRuinsTestPal[128];
extern const u16 sRuinsTestPal_SymbolShot_Frame1[8];
extern const u16 sRuinsTestPal_SymbolShot_Frame2[8];
extern const u16 sRuinsTestPal_SymbolShot_Frame3[8];
extern const u16 sRuinsTestPal_SymbolShot_Frame4[8];
extern const u16 sRuinsTestPal_SymbolShot_Frame5[8];
extern const u16 sRuinsTestPal_SymbolShot_Frame6[8];
extern const u16 sRuinsTestPal_SamusReflection[15 * 16];
extern const u16 sRuinsTestPal_SamusReflectionFullSuit[15 * 16];

extern const struct FrameData sRuinsTestSamusReflectionOam[2];

extern const struct FrameData sRuinsTestGhostOutlineOam_Spawning[9];

extern const struct FrameData sRuinsTestGhostOam_NotMoving[2];
extern const struct FrameData sRuinsTestGhostOam_Moving[7];
extern const struct FrameData sRuinsTestGhostOam_SymbolPlaced[2];

extern const struct FrameData sRuinsTestSymbolOam_FourSymbols[14];
extern const struct FrameData sRuinsTestSymbolOam_Merging[3];
extern const struct FrameData sRuinsTestSymbolOam_Disappearing[7];

extern const struct FrameData sRuinsTestOam_TurningIntoReflection[13];
extern const struct FrameData sRuinsTestReflectionCoverOam[3];
extern const struct FrameData sRuinsTestOam_Symbol[5];

extern const struct FrameData sRuinsTestShootableSymbolOam_Spawning[10];
extern const struct FrameData sRuinsTestShootableSymbolOam_Spawned[7];
extern const struct FrameData sRuinsTestShootableSymbolOam_Despawning[5];
extern const struct FrameData sRuinsTestShootableSymbolOam_TurningIntoSymbol[9];

extern const struct FrameData sRuinsTestGhostOam_SymbolShot[2];
extern const struct FrameData sRuinsTestGhostOam_SymbolPlacing[14];

extern const struct FrameData sRuinsTestOam_Despawn[6];
extern const struct FrameData sRuinsTestOam_Unused[9];
extern const struct FrameData sRuinsTestOam_Spawning[9];

extern const struct FrameData sRuinsTestLightningOam_InAir[12];
extern const struct FrameData sRuinsTestLightningOam_GoingOnGround[9];
extern const struct FrameData sRuinsTestLightningOam_OnGroundHorizontal[17];
extern const struct FrameData sRuinsTestLightningOam_OnGroundVertical[17];

extern const struct FrameData sRuinsTestGhostOutlineOam_ShootingGroundLightning[9];

#endif /* RUINS_TEST_DATA_H */
