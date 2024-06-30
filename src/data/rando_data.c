#include "data/rando_data.h"
#include "macros.h"

#include "constants/connection.h"

#include "data/animated_tiles_data.h"
#include "data/common_pals.h"
#include "data/sprites/morph_ball.h"
#include "data/sprites/chozo_statue.h"
#include "data/sprites/charge_beam.h"
#include "data/sprites/power_grip.h"
#include "data/sprites/unknown_item_chozo_statue.h"


const u8 sRandoLongBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoChargeBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoPlasmaBeamGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/plasmabeam.gfx");  // paperkoopa
const u8 sRandoIceBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoWaveBeamGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoMorphBallGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoBombGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoVariaSuitGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoGravitySuitGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/gravitysuit.gfx");  // paperkoopa
const u8 sRandoSpeedBoosterGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoHiJumpGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoScrewAttackGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoSpaceJumpGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/spacejump.gfx");  // paperkoopa
const u8 sRandoPowerGripGfx[RANDO_GRAPHICS_SIZE] = {};
const u8 sRandoNothingGfx[RANDO_GRAPHICS_SIZE] = INCBIN_U8("data/rando/itemsphere.gfx");  // @lilDavid
const u8 sRandoAPLogoGfx[RANDO_GRAPHICS_SIZE * 3] = INCBIN_U8("data/rando/aplogo.gfx");  // @lilDavid + paperkoopa

const u16 sRandoPlasmaBeamPal[0x20] = INCBIN_U16("data/rando/plasmabeam.pal");
const u16 sRandoGravitySuitPal[0x20] = INCBIN_U16("data/rando/gravitysuit.pal");
const u16 sRandoSpaceJumpPal[0x20] = INCBIN_U16("data/rando/spacejump.pal");  // Colored similar to SM by popular vote at https://discord.com/channels/731205301247803413/1106280250528235620/1252962577429041204
const u16 sRandoNothingPal[0x20] = INCBIN_U16("data/rando/itemsphere.pal");
const u16 sRandoAPLogoPal[0x20] = INCBIN_U16("data/rando/aplogo.pal");

const struct ItemGraphicsInfo sItemGfxPointers[ITEM_MAX] = {
    [ITEM_ENERGY_TANK] = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE, sCommonTilesPal - 1},
    [ITEM_MISSILE_TANK] = {sAnimatedTankGfx, sCommonTilesPal - 1},
    [ITEM_SUPER_MISSILE_TANK] = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE * 3, sCommonTilesPal - 1},
    [ITEM_POWER_BOMB_TANK] = {sAnimatedTankGfx + RANDO_GRAPHICS_SIZE * 2, sCommonTilesPal - 1},
    [ITEM_LONG_BEAM] = {sRandoLongBeamGfx, sChozoStatueLongBeamPal},
    [ITEM_CHARGE_BEAM] = {sRandoChargeBeamGfx, sChargeBeamPal},
    [ITEM_ICE_BEAM] = {sRandoIceBeamGfx, sChozoStatueIceBeamPal},
    [ITEM_WAVE_BEAM] = {sRandoWaveBeamGfx, sChozoStatueWaveBeamPal},
    [ITEM_PLASMA_BEAM] = {sRandoPlasmaBeamGfx, sRandoPlasmaBeamPal},
    [ITEM_BOMB] = {sRandoBombGfx, sChozoStatueBombsPal},
    [ITEM_VARIA_SUIT] = {sRandoVariaSuitGfx, sChozoStatueVariaPal},
    [ITEM_GRAVITY_SUIT] = {sRandoGravitySuitGfx, sRandoGravitySuitPal},
    [ITEM_MORPH_BALL] = {sRandoMorphBallGfx, sMorphBallPal},
    [ITEM_SPEED_BOOSTER] = {sRandoSpeedBoosterGfx, sChozoStatueSpeedboosterPal},
    [ITEM_HIJUMP_BOOTS] = {sRandoHiJumpGfx, sChozoStatueHighJumpPal},
    [ITEM_SCREW_ATTACK] = {sRandoScrewAttackGfx, sChozoStatueScrewAttackPal},
    [ITEM_SPACE_JUMP] = {sRandoSpaceJumpGfx, sRandoSpaceJumpPal},
    [ITEM_POWER_GRIP] = {sRandoPowerGripGfx, sPowerGripPal},
    [ITEM_NOTHING] = {sRandoNothingGfx, sRandoNothingPal},
    [ITEM_AP_FILLER] = {sRandoAPLogoGfx, sRandoAPLogoPal},
    [ITEM_AP_PROGRESSION] = {sRandoAPLogoGfx + RANDO_GRAPHICS_SIZE, sRandoAPLogoPal},
    [ITEM_AP_USEFUL] = {sRandoAPLogoGfx + RANDO_GRAPHICS_SIZE * 2, sRandoAPLogoPal},
};

// Affected sprites capitalized or written in parens
const u8 sRandoMultiworldDangerousSpritesets[] = {
      3,  // Kraid enemies, GADORA
      7,  // KRAID
     35,  // GLASS TUNNEL SHARDS, space pirate
     37,  // Hives, BUGS
//   45,  // Four item banners? (unused)
     54,  // Metroid, rinkas (green rinka)
     55,  // RIDLEY
     67,  // Mother Brain, ZEBETITES, TURRETS, RINKAS
     73,  // Vines, gerutas (green geruta)
//   75,  // CROCOMIRE - unused
     81,  // Brinstar-Kraid elevator, crumbling statue, GEEMER
     86,  // TOURIAN GATE
//   88,  // Chozodia save station, SPACE PIRATE - handled separately
     93,  // SPACE PIRATE SHIP, space pirate
     97,  // Imago, violas (unused Imago parts?)
    100,  // Space pirate, atomic (atomic lightning)
    101,  // MECHA RIDLEY
//  103,  // Chozodia map station, SPACE PIRATE - handled separately
};

// Comments are descriptions of rooms and what graphics the message overwrites
const u8 sRandoMultiworldDangerousRooms[][2] = {
    {AREA_BRINSTAR, 8},  // Elevator to Kraid (geemer)
    {AREA_BRINSTAR, 10},  // Tourian gateway (statues)
    {AREA_BRINSTAR, 13},  // Hallway on the way to bridge and hive (bugs)
    {AREA_KRAID, 29},  // Gadora to boss (gadora)
    {AREA_KRAID, 30},  // Kraid boss room (Kraid)
    {AREA_RIDLEY, 12},  // Ridley boss room (Ridley)
    {AREA_RIDLEY, 24},  // Tangle vine room (green geruta)
    {AREA_TOURIAN, 3},  // Farming room (green rinkas)
    {AREA_TOURIAN, 4},  // Mother Brain boss room (zebetites, turrets, and rinkas)
    {AREA_TOURIAN, 18},  // S-shaped room (green rinkas)
//  {AREA_CHOZODIA, 4},  // Save room (space pirate) - handled separately
//  {AREA_CHOZODIA, 11},  // Map room (space pirate) - handled separately
    {AREA_CHOZODIA, 13},  // TBD (atomic lightning)
//  {AREA_CHOZODIA, 15},  // Save room (space pirate) - handled separately
    {AREA_CHOZODIA, 18},  // TBD (atomic lightning)
//  {AREA_CHOZODIA, 21},  // Save room (space pirate) - handled separately
    {AREA_CHOZODIA, 23},  // Glass tube room (tube shards)
//  {AREA_CHOZODIA, 27},  // Save room (space pirate) - handled separately
//  {AREA_CHOZODIA, 40},  // Save room (space pirate) - handled separately
    {AREA_CHOZODIA, 42},  // Chozo ruins test boss room (ruins test)
    {AREA_CHOZODIA, 48},  // TBD (ship)
    {AREA_CHOZODIA, 58},  // TBD (atomic lightning)
//  {AREA_CHOZODIA, 61},  // Save room (space pirate) - handled separately
    {AREA_CHOZODIA, 72},  // Mecha Ridley boss room (Mecha Ridley)
//  {AREA_CHOZODIA, 88},  // Save room (space pirate) - handled separately
    {AREA_CHOZODIA, 92},  // TBD (ship)
};

// Can be allowed or disallowed depending on chase status
const u8 sRandoChozodiaSaveAndMapRooms[] = {
    4, 11, 15, 21, 27, 40, 61, 88
};
