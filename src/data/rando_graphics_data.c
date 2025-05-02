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
const u8 sRandoPlasmaBeamGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/plasmabeam.gfx");  // @Paperkoopa
const u8 sRandoIceBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoWaveBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoMorphBallGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoBombGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoVariaSuitGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoUnknownGravitySuitGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoGravitySuitGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/gravitysuit.gfx");  // @Paperkoopa
const u8 sRandoSpeedBoosterGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoHiJumpGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoScrewAttackGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoUnknownSpaceJumpGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoSpaceJumpGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/spacejump.gfx");  // @Paperkoopa
const u8 sRandoPowerGripGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoNothingGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/itemsphere.gfx");  // @lilDavid

const u16 sRandoPlasmaBeamPal[PALETTE_SIZE] = INCBIN_U16("data/rando/plasmabeam.pal");
const u16 sRandoGravitySuitPal[PALETTE_SIZE] = INCBIN_U16("data/rando/gravitysuit.pal");
const u16 sRandoSpaceJumpPal[PALETTE_SIZE] = INCBIN_U16("data/rando/spacejump.pal");  // Colored similar to SM by popular vote at https://discord.com/channels/731205301247803413/1106280250528235620/1252962577429041204
const u16 sRandoNothingPal[PALETTE_SIZE] = INCBIN_U16("data/rando/itemsphere.pal");

const struct RandoSprite sRandoEnergyTankSprite = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE, sCommonTilesPal};
const struct RandoSprite sRandoMissileTankSprite = {sAnimatedTankGfx, sCommonTilesPal};
const struct RandoSprite sRandoSuperMissileTankSprite = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE * 3, sCommonTilesPal};
const struct RandoSprite sRandoPowerBombTankSprite = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE * 2, sCommonTilesPal};
const struct RandoSprite sRandoLongBeamSprite = {sRandoLongBeamGfx, sChozoStatueLongBeamPal};
const struct RandoSprite sRandoChargeBeamSprite = {sRandoChargeBeamGfx, sChargeBeamPal};
const struct RandoSprite sRandoIceBeamSprite = {sRandoIceBeamGfx, sChozoStatueIceBeamPal};
const struct RandoSprite sRandoWaveBeamSprite = {sRandoWaveBeamGfx, sChozoStatueWaveBeamPal};
const struct RandoSprite sRandoUnknownPlasmaBeamSprite = {sRandoUnknownPlasmaBeamGfx, sChozoStatuePlasmaBeamPal};
const struct RandoSprite sRandoPlasmaBeamSprite = {sRandoPlasmaBeamGfx, sRandoPlasmaBeamPal};
const struct RandoSprite sRandoBombSprite = {sRandoBombGfx, sChozoStatueBombsPal};
const struct RandoSprite sRandoVariaSuitSprite = {sRandoVariaSuitGfx, sChozoStatueVariaPal};
const struct RandoSprite sRandoUnknownGravitySuitSprite = {sRandoUnknownGravitySuitGfx, sChozoStatueGravitySuitPal};
const struct RandoSprite sRandoGravitySuitSprite = {sRandoGravitySuitGfx, sRandoGravitySuitPal};
const struct RandoSprite sRandoMorphBallSprite = {sRandoMorphBallGfx, sMorphBallPal};
const struct RandoSprite sRandoSpeedBoosterSprite = {sRandoSpeedBoosterGfx, sChozoStatueSpeedboosterPal};
const struct RandoSprite sRandoHiJumpSprite = {sRandoHiJumpGfx, sChozoStatueHighJumpPal};
const struct RandoSprite sRandoScrewAttackSprite = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal};
const struct RandoSprite sRandoUnknownSpaceJumpSprite = {sRandoUnknownSpaceJumpGfx, sChozoStatueSpaceJumpPal};
const struct RandoSprite sRandoSpaceJumpSprite = {sRandoSpaceJumpGfx, sRandoSpaceJumpPal};
const struct RandoSprite sRandoPowerGripSprite = {sRandoPowerGripGfx, sPowerGripPal};
const struct RandoSprite sRandoNothingSprite = {sRandoNothingGfx, sRandoNothingPal};
