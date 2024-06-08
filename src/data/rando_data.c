#include "data/rando_data.h"
#include "macros.h"

#include "data/animated_tiles_data.h"
#include "data/common_pals.h"
#include "data/sprites/morph_ball.h"
#include "data/sprites/chozo_statue.h"
#include "data/sprites/charge_beam.h"
#include "data/sprites/power_grip.h"
#include "data/sprites/unknown_item_chozo_statue.h"


const u8 sRandoLongBeamGfx[384] = INCBIN_U8("data/rando/longbeam.gfx");
const u8 sRandoChargeBeamGfx[384] = INCBIN_U8("data/rando/chargebeam.gfx");
const u8 sRandoPlasmaBeamUnknownGfx[384] = INCBIN_U8("data/rando/plasmabeamunknown.gfx");
const u8 sRandoIceBeamGfx[384] = INCBIN_U8("data/rando/icebeam.gfx");
const u8 sRandoWaveBeamGfx[384] = INCBIN_U8("data/rando/wavebeam.gfx");
const u8 sRandoMorphBallGfx[384] = INCBIN_U8("data/rando/morphball.gfx");
const u8 sRandoBombGfx[384] = INCBIN_U8("data/rando/bomb.gfx");
const u8 sRandoVariaSuitGfx[384] = INCBIN_U8("data/rando/variasuit.gfx");
const u8 sRandoGravitySuitUnknownGfx[384] = INCBIN_U8("data/rando/gravitysuitunknown.gfx");
const u8 sRandoSpeedBoosterGfx[384] = INCBIN_U8("data/rando/speedbooster.gfx");
const u8 sRandoHiJumpGfx[384] = INCBIN_U8("data/rando/hijump.gfx");
const u8 sRandoScrewAttackGfx[384] = INCBIN_U8("data/rando/screwattack.gfx");
const u8 sRandoSpaceJumpUnknownGfx[384] = INCBIN_U8("data/rando/spacejumpunknown.gfx");
const u8 sRandoPowerGripGfx[384] = INCBIN_U8("data/rando/powergrip.gfx");

const struct ItemGraphicsInfo sItemGfxPointers[ITEM_MAX] = {
    [ITEM_ETANK] = {sAnimatedTankGfx + 512, sCommonTilesPal - 1},
    [ITEM_MISSILE] = {sAnimatedTankGfx, sCommonTilesPal - 1},
    [ITEM_SUPER] = {sAnimatedTankGfx + 512 * 3, sCommonTilesPal - 1},
    [ITEM_POWER_BOMB] = {sAnimatedTankGfx + 512 * 2, sCommonTilesPal - 1},
    [ITEM_LONG_BEAM] = {sRandoLongBeamGfx, sChozoStatueLongBeamPal},
    [ITEM_CHARGE_BEAM] = {sRandoChargeBeamGfx, sChargeBeamPal},
    [ITEM_ICE_BEAM] = {sRandoIceBeamGfx, sChozoStatueIceBeamPal},
    [ITEM_WAVE_BEAM] = {sRandoWaveBeamGfx, sChozoStatueWaveBeamPal},
    [ITEM_PLASMA_BEAM] = {sRandoPlasmaBeamUnknownGfx, sChozoStatuePlasmaBeamPal},  // TODO: Non-unknown graphic
    [ITEM_BOMB] = {sRandoBombGfx, sChozoStatueBombsPal},
    [ITEM_VARIA_SUIT] = {sRandoVariaSuitGfx, sChozoStatueVariaPal},
    [ITEM_GRAVITY_SUIT] = {sRandoGravitySuitUnknownGfx, sChozoStatueGravitySuitPal},  // TODO: Non-unknown graphic
    [ITEM_MORPH_BALL] = {sRandoMorphBallGfx, sMorphBallPal},
    [ITEM_SPEED_BOOSTER] = {sRandoSpeedBoosterGfx, sChozoStatueSpeedboosterPal},
    [ITEM_HIJUMP_BOOTS] = {sRandoHiJumpGfx, sChozoStatueHighJumpPal},
    [ITEM_SCREW_ATTACK] = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal},
    [ITEM_SPACE_JUMP] = {sRandoSpaceJumpUnknownGfx, sChozoStatueSpaceJumpPal},  // TODO: Non-unknown graphic
    [ITEM_POWER_GRIP] = {sRandoPowerGripGfx, sPowerGripPal},
    [ITEM_MISSILE_TANK] = {sAnimatedTankGfx, sCommonTilesPal - 1},
    [ITEM_SUPER_MISSILE_TANK] = {sAnimatedTankGfx + 512 * 3, sCommonTilesPal - 1},
    [ITEM_POWER_BOMB_TANK] = {sAnimatedTankGfx + 512 * 2, sCommonTilesPal - 1},
    [ITEM_AP_FILLER] = {sAnimatedTankGfx, sCommonTilesPal - 1},  // TODO
    [ITEM_AP_PROGRESSION] = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal},  // TODO
    [ITEM_AP_USEFUL] = {sRandoChargeBeamGfx, sChargeBeamPal},  // TODO
    [ITEM_AP_TRAP] = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal},  // TODO
};
