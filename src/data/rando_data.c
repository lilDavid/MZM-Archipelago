#include "data/rando_data.h"
#include "macros.h"

#include "data/common_pals.h"
#include "data/sprites/morph_ball.h"
#include "data/sprites/chozo_statue.h"
#include "data/sprites/charge_beam.h"
#include "data/sprites/power_grip.h"
#include "data/sprites/unknown_item_chozo_statue.h"


const u32 sRandoEnergyTankGfx[384 / 4] = INCBIN_U32("data/rando/energytank.gfx");
const u32 sRandoMissileTankGfx[384 / 4] = INCBIN_U32("data/rando/missiletank.gfx");
const u32 sRandoSuperMissileTankGfx[384 / 4] = INCBIN_U32("data/rando/supermissiletank.gfx");
const u32 sRandoPowerBombTankGfx[384 / 4] = INCBIN_U32("data/rando/powerbombtank.gfx");
const u32 sRandoLongBeamGfx[384 / 4] = INCBIN_U32("data/rando/longbeam.gfx");
const u32 sRandoChargeBeamGfx[384 / 4] = INCBIN_U32("data/rando/chargebeam.gfx");
const u32 sRandoPlasmaBeamUnknownGfx[384 / 4] = INCBIN_U32("data/rando/plasmabeamunknown.gfx");
const u32 sRandoIceBeamGfx[384 / 4] = INCBIN_U32("data/rando/icebeam.gfx");
const u32 sRandoWaveBeamGfx[384 / 4] = INCBIN_U32("data/rando/wavebeam.gfx");
const u32 sRandoMorphBallGfx[384 / 4] = INCBIN_U32("data/rando/morphball.gfx");
const u32 sRandoBombGfx[384 / 4] = INCBIN_U32("data/rando/bomb.gfx");
const u32 sRandoVariaSuitGfx[384 / 4] = INCBIN_U32("data/rando/variasuit.gfx");
const u32 sRandoGravitySuitUnknownGfx[384 / 4] = INCBIN_U32("data/rando/gravitysuitunknown.gfx");
const u32 sRandoSpeedBoosterGfx[384 / 4] = INCBIN_U32("data/rando/speedbooster.gfx");
const u32 sRandoHiJumpGfx[384 / 4] = INCBIN_U32("data/rando/hijump.gfx");
const u32 sRandoScrewAttackGfx[384 / 4] = INCBIN_U32("data/rando/screwattack.gfx");
const u32 sRandoSpaceJumpUnknownGfx[384 / 4] = INCBIN_U32("data/rando/spacejumpunknown.gfx");
const u32 sRandoPowerGripGfx[384 / 4] = INCBIN_U32("data/rando/powergrip.gfx");

const struct ItemGraphicsInfo sItemGfxPointers[ITEM_MAX] = {
    [ITEM_ETANK] = {sRandoEnergyTankGfx, sCommonTilesPal - 1},
    [ITEM_MISSILE] = {sRandoMissileTankGfx, sCommonTilesPal - 1},
    [ITEM_SUPER] = {sRandoSuperMissileTankGfx, sCommonTilesPal - 1},
    [ITEM_POWER_BOMB] = {sRandoPowerBombTankGfx, sCommonTilesPal - 1},
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
    [ITEM_MISSILE_TANK] = {sRandoMissileTankGfx, sCommonTilesPal - 1},
    [ITEM_SUPER_MISSILE_TANK] = {sRandoSuperMissileTankGfx, sCommonTilesPal - 1},
    [ITEM_POWER_BOMB_TANK] = {sRandoPowerBombTankGfx, sCommonTilesPal - 1},
    [ITEM_AP_FILLER] = {sRandoMissileTankGfx, sCommonTilesPal - 1},  // TODO
    [ITEM_AP_PROGRESSION] = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal},  // TODO
    [ITEM_AP_USEFUL] = {sRandoChargeBeamGfx, sChargeBeamPal},  // TODO
    [ITEM_AP_TRAP] = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal},  // TODO
};
