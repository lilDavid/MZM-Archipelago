#include "data/rando_data.h"
#include "macros.h"

#include "data/animated_tiles_data.h"
#include "data/common_pals.h"
#include "data/sprites/morph_ball.h"
#include "data/sprites/chozo_statue.h"
#include "data/sprites/charge_beam.h"
#include "data/sprites/power_grip.h"
#include "data/sprites/unknown_item_chozo_statue.h"


const u8 sRandoLongBeamGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/longbeam.gfx");
const u8 sRandoChargeBeamGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/chargebeam.gfx");
const u8 sRandoPlasmaBeamUnknownGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/plasmabeamunknown.gfx");
const u8 sRandoIceBeamGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/icebeam.gfx");
const u8 sRandoWaveBeamGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/wavebeam.gfx");
const u8 sRandoMorphBallGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/morphball.gfx");
const u8 sRandoBombGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/bomb.gfx");
const u8 sRandoVariaSuitGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/variasuit.gfx");
const u8 sRandoGravitySuitUnknownGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/gravitysuitunknown.gfx");
const u8 sRandoSpeedBoosterGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/speedbooster.gfx");
const u8 sRandoHiJumpGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/hijump.gfx");
const u8 sRandoScrewAttackGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/screwattack.gfx");
const u8 sRandoSpaceJumpUnknownGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/spacejumpunknown.gfx");
const u8 sRandoPowerGripGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/powergrip.gfx");
const u8 sRandoAPLogoGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/aplogo.gfx");

const u16 sRandoAPLogoPal[0x20] = INCBIN_U16("data/rando/aplogo.pal");

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
    [ITEM_AP_FILLER] = {sRandoAPLogoGfx, sRandoAPLogoPal},  // TODO: Distinguish AP items
    [ITEM_AP_PROGRESSION] = {sRandoAPLogoGfx, sRandoAPLogoPal},  // TODO: Distinguish AP items
    [ITEM_AP_USEFUL] = {sRandoAPLogoGfx, sRandoAPLogoPal},  // TODO: Distinguish AP items
    [ITEM_AP_TRAP] = {sRandoAPLogoGfx, sRandoAPLogoPal},  // TODO: Distinguish AP items
};
