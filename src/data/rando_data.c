#include "data/rando_data.h"
#include "macros.h"

#include "constants/block.h"
#include "constants/connection.h"
#include "constants/samus.h"
#include "constants/text.h"

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

const struct Camera sStartingLocationCamera = {
    .xPosition = 0x800,
    .yPosition = 0x580,
    .xVelocity = 0,
    .yVelocity = 0,
};

// Affected sprites capitalized or written in parens
// Data provided by @Paperkoopa
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
     77,  // CHOZO RUINS TEST, FALLING PILLAR
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
    {AREA_CHOZODIA, 42},  // Chozo ruins test boss room (ruins test and falling pillar)
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

const u8 sRandoDisallowedSamusPoses[] = {
    SPOSE_GRABBED_BY_CHOZO_STATUE,
    SPOSE_SAVING_LOADING_GAME,
    SPOSE_DOWNLOADING_MAP_DATA,
    SPOSE_IN_ESCAPE_SHIP,
};

const u8 sItemMessages[] = {
    [ITEM_ENERGY_TANK] = MESSAGE_ENERGY_TANK_ACQUIRED,
    [ITEM_MISSILE_TANK] = MESSAGE_MISSILE_TANK_ACQUIRED,
    [ITEM_SUPER_MISSILE_TANK] = MESSAGE_SUPER_MISSILE_TANK_ACQUIRED,
    [ITEM_POWER_BOMB_TANK] = MESSAGE_POWER_BOMB_TANK_ACQUIRED,
    [ITEM_LONG_BEAM] = MESSAGE_LONG_BEAM,
    [ITEM_CHARGE_BEAM] = MESSAGE_CHARGE_BEAM,
    [ITEM_ICE_BEAM] = MESSAGE_ICE_BEAM,
    [ITEM_WAVE_BEAM] = MESSAGE_WAVE_BEAM,
    [ITEM_PLASMA_BEAM] = MESSAGE_PLASMA_BEAM,
    [ITEM_BOMB] = MESSAGE_BOMB,
    [ITEM_VARIA_SUIT] = MESSAGE_VARIA_SUIT,
    [ITEM_GRAVITY_SUIT] = MESSAGE_GRAVITY_SUIT,
    [ITEM_MORPH_BALL] = MESSAGE_MORPH_BALL,
    [ITEM_SPEED_BOOSTER] = MESSAGE_SPEED_BOOSTER,
    [ITEM_HIJUMP_BOOTS] = MESSAGE_HIGH_JUMP,
    [ITEM_SCREW_ATTACK] = MESSAGE_SCREW_ATTACK,
    [ITEM_SPACE_JUMP] = MESSAGE_SPACE_JUMP,
    [ITEM_POWER_GRIP] = MESSAGE_POWER_GRIP,
    [ITEM_NOTHING] = MESSAGE_NOTHING_ACQUIRED,
    [ITEM_AP_FILLER] = MESSAGE_DUMMY,
    [ITEM_AP_PROGRESSION] = MESSAGE_DUMMY,
    [ITEM_AP_USEFUL] = MESSAGE_DUMMY,
};

const u8 sRegionLocationOffsets[] = {
    [AREA_BRINSTAR] = 0,
    [AREA_KRAID] = RC_BRINSTAR_MAX,
    [AREA_NORFAIR] = RC_KRAID_MAX,
    [AREA_RIDLEY] = RC_NORFAIR_MAX,
    [AREA_TOURIAN] = RC_RIDLEY_MAX,
    [AREA_CRATERIA] = RC_TOURIAN_MAX,
    [AREA_CHOZODIA] = RC_CRATERIA_MAX,
    [AREA_CHOZODIA + 1] = RC_CHOZODIA_MAX,
};

const u8 sRoomItemsBrinstar[] = {
     1, RC_BRINSTAR_MORPH_BALL_CANNON,
     2, RC_BRINSTAR_CEILING_ETANK,
    12, RC_BRINSTAR_FIRST_MISSILE,
    14, RC_BRINSTAR_UNDER_BRIDGE,
    15, RC_BRINSTAR_BEHIND_HIVE,
    19, RC_BRINSTAR_POST_HIVE_MISSILE,
    19, RC_BRINSTAR_POST_HIVE_ETANK,
    21, RC_BRINSTAR_UPPER_PILLAR_MISSILE,
    23, RC_BRINSTAR_ACID_NEAR_VARIA,
    25, RC_BRINSTAR_BEHIND_BOMBS,
    29, RC_BRINSTAR_TOP_MISSILE,
    40, RC_BRINSTAR_SPEED_BOOSTER_SHORTCUT_MISSILE,
    41, RC_BRINSTAR_MISSILE_ABOVE_SUPER,
    41, RC_BRINSTAR_SUPER_MISSILE,
};

const u8 sRoomItemsKraid[] = {
     1, RC_KRAID_PILLAR_MISSILE,
     2, RC_KRAID_UPPER_RIGHT_MORPH_BALL_CANNON,
     4, RC_KRAID_WORM_ETANK,
     7, RC_KRAID_SAVE_ROOM_MISSILE,
     8, RC_KRAID_ACID_BALLSPARK,
     9, RC_KRAID_SPEED_JUMP,
    10, RC_KRAID_CRUMBLE_BLOCK_MISSILE,
    17, RC_KRAID_ACID_FALL,
    21, RC_KRAID_QUAD_BALL_CANNON_ROOM,
    26, RC_KRAID_GIANT_HOPPERS_MISSILE,
    38, RC_KRAID_WORM_MISSILE,
};

const u8 sRoomItemsNorfair[] = {
     1, RC_NORFAIR_POWER_GRIP_MISSILE,
     3, RC_NORFAIR_UNDER_CRATERIA_ELEVATOR,
     4, RC_NORFAIR_BIG_ROOM,
     5, RC_NORFAIR_RIGHT_SHAFT_LOWER,
     5, RC_NORFAIR_RIGHT_SHAFT_BOTTOM,
    10, RC_NORFAIR_HEATED_ROOM_ABOVE_ICE_BEAM,
    17, RC_NORFAIR_SCREW_ATTACK_MISSILE,
    28, RC_NORFAIR_BOTTOM_HEATED_ROOM_FIRST,
    28, RC_NORFAIR_BOTTOM_HEATED_ROOM_SECOND,
    32, RC_NORFAIR_SPACE_BOOST_MISSILE,
    32, RC_NORFAIR_SPACE_BOOST_SUPER_MISSILE,
    37, RC_NORFAIR_HEATED_ROOM_UNDER_BRINSTAR_ELEVATOR,
    38, RC_NORFAIR_BOMB_TRAP,
    42, RC_NORFAIR_LARVA_CEILING_ETANK,
    46, RC_NORFAIR_LARVA_CEILING_ETANK,
    47, RC_NORFAIR_BEHIND_TOP_CHOZO_STATUE,
    55, RC_NORFAIR_POWER_BOMB,
    55, RC_NORFAIR_LAVA_MISSILE,
};

const u8 sRoomItemsRidley[] = {
     4, RC_RIDLEY_FAKE_FLOOR_ETANK,
     6, RC_RIDLEY_WEST_PILLAR,
     9, RC_RIDLEY_PILLAR_MISSILE,
    10, RC_RIDLEY_BALL_ROOM_MISSILE,
    10, RC_RIDLEY_BALL_ROOM_SUPER,
    13, RC_RIDLEY_ETANK_BEHIND_GRAVITY,
    14, RC_RIDLEY_OWL_ETANK,
    16, RC_RIDLEY_NE_CORNER_MISSILE,
    17, RC_RIDLEY_FAKE_LAVA_MISSILE,
    18, RC_RIDLEY_LONG_HALL,
    19, RC_RIDLEY_IMAGO_SUPER_MISSILE,
    22, RC_RIDLEY_AFTER_SIDEHOPPER_HALL_UPPER,
    22, RC_RIDLEY_AFTER_SIDEHOPPER_HALL_LOWER,
    23, RC_RIDLEY_UPPER_BALL_CANNON,
    23, RC_RIDLEY_LOWER_BALL_CANNON,
    29, RC_RIDLEY_SW_PUZZLE_TOP,
    29, RC_RIDLEY_SW_PUZZLE_BOTTOM,
    30, RC_RIDLEY_BOMB_PUZZLE,
    31, RC_RIDLEY_SPEED_JUMP,
};

const u8 sRoomItemsTourian[] = {
    7, RC_TOURIAN_UNDER_MOTHER_BRAIN,
    8, RC_TOURIAN_LEFT_OF_MOTHER_BRAIN,
};

const u8 sRoomItemsCrateria[] = {
     0, RC_CRATERIA_LANDING_SITE_BALLSPARK,
     5, RC_CRATERIA_LANDING_SITE_BALLSPARK,
     7, RC_CRATERIA_MOAT,
     9, RC_CRATERIA_EAST_BALLSPARK,
     9, RC_CRATERIA_NE_CORNER,
    14, RC_CRATERIA_STATUE_WATER,
};

const u8 sRoomItemsChozodia[] = {
    10, RC_CHOZODIA_MOTHERSHIP_CEILING_NEAR_ZSS_START,
    14, RC_CHOZODIA_WORKBOT_SUPER,
    24, RC_CHOZODIA_GLASS_TUBE_ETANK,
    26, RC_CHOZODIA_UNDER_CHOZO_GHOST_AREA_WATER,
    34, RC_CHOZODIA_UPPER_CRATERIA_DOOR,
    41, RC_CHOZODIA_CHOZO_GHOST_AREA_MORPH_TUNNEL_ABOVE_WATER,
    41, RC_CHOZODIA_CHOZO_GHOST_AREA_UNDERWATER,
    47, RC_CHOZODIA_ORIGINAL_POWER_BOMB,
    49, RC_CHOZODIA_NEXT_TO_ORIGINAL_POWER_BOMB,
    54, RC_CHOZODIA_LAVA_SUPER,
    65, RC_CHOZODIA_ZOOMER_MAZE,
    66, RC_CHOZODIA_BOMB_MAZE,
    71, RC_CHOZODIA_UNDER_MECHA_RIDLEY_HALLWAY,
    73, RC_CHOZODIA_SHORTCUT_SUPER,
    78, RC_CHOZODIA_CHOZO_GHOST_AREA_LONG_SHINESPARK,
    87, RC_CHOZODIA_SE_CORNER_IN_HULL,
    89, RC_CHOZODIA_NEAR_UPPER_CRATERIA_DOOR,
    90, RC_CHOZODIA_CHOZO_GHOST_AREA_MORPH_TUNNEL_ABOVE_WATER,
    90, RC_CHOZODIA_CHOZO_GHOST_AREA_UNDERWATER,
    95, RC_CHOZODIA_GLASS_TUBE_POWER_BOMB,
};

const u8* const sRandoAreaItemLists[AREA_NORMAL_END + 1] = {
    [AREA_BRINSTAR] = sRoomItemsBrinstar,
    [AREA_KRAID] = sRoomItemsKraid,
    [AREA_NORFAIR] = sRoomItemsNorfair,
    [AREA_RIDLEY] = sRoomItemsRidley,
    [AREA_TOURIAN] = sRoomItemsTourian,
    [AREA_CRATERIA] = sRoomItemsCrateria,
    [AREA_CHOZODIA] = sRoomItemsChozodia,
};

const u8 sRandoAreaItemListLengths[AREA_NORMAL_END + 1] = {
    [AREA_BRINSTAR] = ARRAY_SIZE(sRoomItemsBrinstar),
    [AREA_KRAID] = ARRAY_SIZE(sRoomItemsKraid),
    [AREA_NORFAIR] = ARRAY_SIZE(sRoomItemsNorfair),
    [AREA_RIDLEY] = ARRAY_SIZE(sRoomItemsRidley),
    [AREA_TOURIAN] = ARRAY_SIZE(sRoomItemsTourian),
    [AREA_CRATERIA] = ARRAY_SIZE(sRoomItemsCrateria),
    [AREA_CHOZODIA] = ARRAY_SIZE(sRoomItemsChozodia),
};

const u8 sRandoItemToTankTilemap[4] = {
    [ITEM_ENERGY_TANK] = 0x45,
    [ITEM_MISSILE_TANK] = 0x41,
    [ITEM_SUPER_MISSILE_TANK] = 0x4D,
    [ITEM_POWER_BOMB_TANK] = 0x49,
};

const u8 sRandoAnimatedTileGaps[8] = {
    [0] = 0,
    [1] = 0,
    [2] = 12,
    [3] = 8,
    [4] = 2,
    [5] = 4,
    [6] = 3,
    [7] = 9,
};

// Created with the help of @Paperkoopa
const u8 sRandoPaletteSlots[79 * 2] = {
    13, 14,
    6, 7,
    9, 14,
    9, 14,
    10, 11,
    6, 7,
    6, 8,
    7, 8,
    7, 8,
    7, 8,
    10, 11,
    11, 12,
    8, 10,
    6, 15,
    14, 15,
    4, 10,
    10, 11,
    7, 8,
    6, 7,
    8, 15,
    7, 8,
    12, 13,
    13, 14,
    8, 13,
    3, 10,
    7, 8,
    3, 8,
    11, 13,
    3, 14,
    8, 11,
    8, 15,
    9, 14,
    9, 14,
    10, 11,
    7, 8,
    3, 12,
    3, 10,
    8, 10,
    6, 7,
    10, 11,
    3, 11,
    3, 11,
    3, 6,
    3, 14,
    3, 14,
    3, 14,
    3, 9,
    4, 14,
    10, 13,
    13, 14,
    UCHAR_MAX, UCHAR_MAX,
    8, 10,
    3, UCHAR_MAX,
    11, 12,
    10, 11,
    3, UCHAR_MAX,
    3, 13,
    3, UCHAR_MAX,
    3, UCHAR_MAX,
    3, UCHAR_MAX,
    3, 15,  // Clobbers row 15
    6, 11,
    11, 12,
    4, 14,
    6, 10,
    3, 8,
    4, 5,
    11, 12,
    8, 14,
    3, 8,
    13, 14,
    15, UCHAR_MAX,  // Clobbers row 15
    9, 10,
    9, 14,
    3, UCHAR_MAX,
    9, 11,
    3, 7,
    3, 7,
    3, 6,
};
