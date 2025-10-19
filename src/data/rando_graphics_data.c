#include "data/rando_graphics_data.h"

#include "macros.h"

#include "data/animated_tiles_data.h"
#include "data/common_pals.h"
#include "data/sprites/charge_beam.h"
#include "data/sprites/chozo_statue.h"
#include "data/sprites/morph_ball.h"
#include "data/sprites/power_grip.h"
#include "data/sprites/unknown_item_chozo_statue.h"


const u8 sRandoLongBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoChargeBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoUnknownPlasmaBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoIceBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoWaveBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoMorphBallGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoBombGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoVariaSuitGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoUnknownGravitySuitGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoSpeedBoosterGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoHiJumpGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoScrewAttackGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoUnknownSpaceJumpGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoPowerGripGfx[RANDO_GRAPHICS_SIZE] = {};

const struct RandoSprite sRandoEnergyTankSprite = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE, sCommonTilesPal};
const struct RandoSprite sRandoMissileTankSprite = {sAnimatedTankGfx, sCommonTilesPal};
const struct RandoSprite sRandoSuperMissileTankSprite = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE * 3, sCommonTilesPal};
const struct RandoSprite sRandoPowerBombTankSprite = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE * 2, sCommonTilesPal};
const struct RandoSprite sRandoLongBeamSprite = {sRandoLongBeamGfx, sChozoStatueLongBeamPal};
const struct RandoSprite sRandoChargeBeamSprite = {sRandoChargeBeamGfx, sChargeBeamPal};
const struct RandoSprite sRandoIceBeamSprite = {sRandoIceBeamGfx, sChozoStatueIceBeamPal};
const struct RandoSprite sRandoWaveBeamSprite = {sRandoWaveBeamGfx, sChozoStatueWaveBeamPal};
const struct RandoSprite sRandoUnknownPlasmaBeamSprite = {sRandoUnknownPlasmaBeamGfx, sChozoStatuePlasmaBeamPal};
const struct RandoSprite sRandoBombSprite = {sRandoBombGfx, sChozoStatueBombsPal};
const struct RandoSprite sRandoVariaSuitSprite = {sRandoVariaSuitGfx, sChozoStatueVariaPal};
const struct RandoSprite sRandoUnknownGravitySuitSprite = {sRandoUnknownGravitySuitGfx, sChozoStatueGravitySuitPal};
const struct RandoSprite sRandoMorphBallSprite = {sRandoMorphBallGfx, sMorphBallPal};
const struct RandoSprite sRandoSpeedBoosterSprite = {sRandoSpeedBoosterGfx, sChozoStatueSpeedboosterPal};
const struct RandoSprite sRandoHiJumpSprite = {sRandoHiJumpGfx, sChozoStatueHighJumpPal};
const struct RandoSprite sRandoScrewAttackSprite = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal};
const struct RandoSprite sRandoUnknownSpaceJumpSprite = {sRandoUnknownSpaceJumpGfx, sChozoStatueSpaceJumpPal};
const struct RandoSprite sRandoPowerGripSprite = {sRandoPowerGripGfx, sPowerGripPal};

const u16 sRandoOam_EnergyDNAHeader[] = {
    8,
    // vanilla energy
    OAM_ENTRY(-16, -2, OAM_DIMS_16x16, 0, 684, 3, 0),
    OAM_ENTRY(8, 0, OAM_DIMS_32x8, 0, 724, 3, 0),
    OAM_ENTRY(8, 0x20, OAM_DIMS_32x8, 0, 724, 3, 0),
    OAM_ENTRY(8, 0x40, OAM_DIMS_8x8, 0, 728, 3, 0),
    // rando DNA
    OAM_ENTRY(-3, 0x48, OAM_DIMS_16x16, 0, 720, 3, 0),
    OAM_ENTRY(5, 0x48, OAM_DIMS_16x8, 0, 722, 3, 0),
    OAM_ENTRY(8, 0x58, OAM_DIMS_32x8, 0, 724, 3, 0),
    OAM_ENTRY(8, 0x78, OAM_DIMS_8x8, 0, 728, 3, 0),
};
