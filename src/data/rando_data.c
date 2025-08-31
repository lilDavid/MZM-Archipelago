#include "data/rando_data.h"
#include "macros.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/samus.h"
#include "constants/sprite.h"

#include "structs/rando.h"


const struct RandoItem sEmptyIncomingItem = {
    .itemType = RANDO_ITEM_NONE,
    .value = 0,
};

const struct RandoMessage sEmptyRandoMessage = {
    .data = NULL,
    .messageID = MESSAGE_DUMMY,
    .oneLine = FALSE,
    .soundEffect = MUSIC_NONE,
};

const struct StartingLocationData sStartingLocation = {
    .samus = {
        .xPosition = 39 * BLOCK_SIZE + HALF_BLOCK_SIZE,
        .yPosition = 30 * BLOCK_SIZE - 1,
        .timer = 0,
        .standingStatus = STANDING_GROUND,
    },
    .camera = {
        .xPosition = 32 * BLOCK_SIZE,
        .yPosition = 22 * BLOCK_SIZE,
        .xVelocity = 0,
        .yVelocity = 0,
    },
    .area = AREA_BRINSTAR,
    .room = 0,
    .lastDoorUsed = 0,
    .useMotherShipDoors = FALSE,
};

// Affected sprites capitalized or written in parens
// Data provided by @Paperkoopa
const u8 sRandoMultiworldDangerousSpritesets[] = {
      3,  // Kraid enemies, GADORA
//    7,  // KRAID
     35,  // GLASS TUNNEL SHARDS, space pirate
     37,  // Hives, BUGS
//   45,  // Four item banners? (unused)
     54,  // Metroid, rinkas (green rinka)
//   55,  // RIDLEY
     67,  // Mother Brain, ZEBETITES, TURRETS, RINKAS
     73,  // Vines, gerutas (green geruta)
//   75,  // CROCOMIRE - unused
//   77,  // CHOZO RUINS TEST, FALLING PILLAR
     81,  // Brinstar-Kraid elevator, crumbling statue, GEEMER
     86,  // TOURIAN GATE
//   88,  // Chozodia save station, SPACE PIRATE - handled separately
     93,  // SPACE PIRATE SHIP, space pirate
     97,  // Imago, violas (unused Imago parts?)
    100,  // Space pirate, atomic (atomic lightning)
//  101,  // MECHA RIDLEY
//  103,  // Chozodia map station, SPACE PIRATE - handled separately
};

// Comments are descriptions of rooms and what graphics the message overwrites
const u8 sRandoMultiworldDangerousRooms[][2] = {
    {AREA_BRINSTAR, 8},  // Elevator to Kraid (geemer)
    {AREA_BRINSTAR, 10},  // Tourian gateway (statues)
    {AREA_BRINSTAR, 13},  // Hallway on the way to bridge and hive (bugs)
    {AREA_KRAID, 29},  // Gadora to boss (gadora)
//  {AREA_KRAID, 30},  // Kraid boss room (Kraid)
//  {AREA_RIDLEY, 12},  // Ridley boss room (Ridley)
    {AREA_RIDLEY, 24},  // Tangle vine room (green geruta)
    {AREA_TOURIAN, 3},  // Farming room (green rinkas)
    {AREA_TOURIAN, 4},  // Mother Brain boss room (zebetites, turrets, and rinkas)
    {AREA_TOURIAN, 18},  // S-shaped room (green rinkas)
//  {AREA_CHOZODIA, 4},  // Save room (space pirate)
//  {AREA_CHOZODIA, 11},  // Map room (space pirate)
    {AREA_CHOZODIA, 13},  // TBD (atomic lightning)
//  {AREA_CHOZODIA, 15},  // Save room (space pirate)
    {AREA_CHOZODIA, 18},  // TBD (atomic lightning)
//  {AREA_CHOZODIA, 21},  // Save room (space pirate)
    {AREA_CHOZODIA, 23},  // Glass tube room (tube shards)
//  {AREA_CHOZODIA, 27},  // Save room (space pirate)
//  {AREA_CHOZODIA, 40},  // Save room (space pirate)
//  {AREA_CHOZODIA, 42},  // Chozo ruins test boss room (ruins test and falling pillar)
    {AREA_CHOZODIA, 48},  // TBD (ship)
    {AREA_CHOZODIA, 58},  // TBD (atomic lightning)
//  {AREA_CHOZODIA, 61},  // Save room (space pirate)
//  {AREA_CHOZODIA, 72},  // Mecha Ridley boss room (Mecha Ridley)
//  {AREA_CHOZODIA, 88},  // Save room (space pirate)
    {AREA_CHOZODIA, 92},  // TBD (ship)
};

const u8 sRandoDisallowedExistingSprites[] = {
    PSPRITE_RIDLEY,
    PSPRITE_RUINS_TEST,
    PSPRITE_KRAID,
    PSPRITE_AREA_BANNER,
    PSPRITE_MECHA_RIDLEY,
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

const u8 sRegionLocationOffsets[] = {
    [AREA_BRINSTAR] = 0,
    [AREA_KRAID] = RC_BRINSTAR_MAX,
    [AREA_NORFAIR] = RC_KRAID_MAX,
    [AREA_RIDLEY] = RC_NORFAIR_MAX,
    [AREA_TOURIAN] = RC_RIDLEY_MAX,
    [AREA_CRATERIA] = RC_TOURIAN_MAX,
    [AREA_CHOZODIA] = RC_CRATERIA_MAX,
    [AREA_NORMAL_COUNT] = RC_CHOZODIA_MAX,
};

const u8 sRoomItemsBrinstar[] = {
     1, RC_BRINSTAR_MORPH_BALL_CANNON,
     2, RC_BRINSTAR_CEILING_ETANK,
    12, RC_BRINSTAR_FIRST_MISSILE,
    14, RC_BRINSTAR_UNDER_BRIDGE,
    15, RC_BRINSTAR_BEHIND_HIVE,
    19, RC_BRINSTAR_POST_HIVE_IN_WALL,
    19, RC_BRINSTAR_POST_HIVE_PILLAR,
    21, RC_BRINSTAR_UPPER_PILLAR,
    23, RC_BRINSTAR_ACID_NEAR_VARIA,
    25, RC_BRINSTAR_BEHIND_BOMBS,
    29, RC_BRINSTAR_RIPPER_CLIMB,
    40, RC_BRINSTAR_SPEED_BOOSTER_SHORTCUT,
    41, RC_BRINSTAR_MAIN_SHAFT_LEFT_ALCOVE,
    41, RC_BRINSTAR_BALLSPARK,
};

const u8 sRoomItemsKraid[] = {
     1, RC_KRAID_RIGHT_HALL_PILLAR,
     2, RC_KRAID_UPPER_RIGHT_MORPH_BALL_CANNON,
     4, RC_KRAID_ZIPLINE_ACTIVATOR_ROOM,
     7, RC_KRAID_SAVE_ROOM_TUNNEL,
     8, RC_KRAID_ACID_BALLSPARK,
     9, RC_KRAID_SPEED_JUMP,
    10, RC_KRAID_ZIPLINE_MORPH_JUMP,
    17, RC_KRAID_ACID_FALL,
    21, RC_KRAID_QUAD_BALL_CANNON_ROOM,
    26, RC_KRAID_BEHIND_GIANT_HOPPERS,
    38, RC_KRAID_UNDER_ACID_WORM,
};

const u8 sRoomItemsNorfair[] = {
     1, RC_NORFAIR_HALLWAY_TO_CRATERIA,
     3, RC_NORFAIR_UNDER_CRATERIA_ELEVATOR,
     4, RC_NORFAIR_BIG_ROOM,
     5, RC_NORFAIR_RIGHT_SHAFT_NEAR_HIJUMP,
     5, RC_NORFAIR_RIGHT_SHAFT_BOTTOM,
    10, RC_NORFAIR_HEATED_ROOM_ABOVE_ICE_BEAM,
    17, RC_NORFAIR_NEXT_TO_SCREW_ATTACK,
    28, RC_NORFAIR_HEATED_ROOM_BELOW_WAVE_LEFT,
    28, RC_NORFAIR_HEATED_ROOM_BELOW_WAVE_RIGHT,
    32, RC_NORFAIR_BEHIND_LOWER_SUPER_MISSILE_DOOR_LEFT,
    32, RC_NORFAIR_BEHIND_LOWER_SUPER_MISSILE_DOOR_RIGHT,
    37, RC_NORFAIR_HEATED_ROOM_UNDER_BRINSTAR_ELEVATOR,
    38, RC_NORFAIR_BOMB_TRAP,
    42, RC_NORFAIR_LARVA_CEILING,
    46, RC_NORFAIR_LARVA_CEILING,
    47, RC_NORFAIR_BEHIND_TOP_CHOZO_STATUE,
    55, RC_NORFAIR_LAVA_DIVE_LEFT,
    55, RC_NORFAIR_LAVA_DIVE_RIGHT,
};

const u8 sRoomItemsRidley[] = {
     4, RC_RIDLEY_FAKE_FLOOR,
     6, RC_RIDLEY_WEST_PILLAR,
     9, RC_RIDLEY_CENTER_PILLAR,
    10, RC_RIDLEY_BALL_ROOM_LOWER,
    10, RC_RIDLEY_BALL_ROOM_UPPER,
    13, RC_RIDLEY_ETANK_BEHIND_UNKNOWN_STATUE,
    14, RC_RIDLEY_UNDER_OWLS,
    16, RC_RIDLEY_NE_CORNER,
    17, RC_RIDLEY_FAKE_LAVA_UNDER_FLOOR,
    18, RC_RIDLEY_LONG_HALL,
    19, RC_RIDLEY_IMAGO_SUPER_MISSILE,
    22, RC_RIDLEY_AFTER_SIDEHOPPER_HALL_UPPER,
    22, RC_RIDLEY_AFTER_SIDEHOPPER_HALL_LOWER,
    23, RC_RIDLEY_UPPER_BALL_CANNON_PUZZLE,
    23, RC_RIDLEY_LOWER_BALL_CANNON_PUZZLE,
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
     9, RC_CRATERIA_NE_CORNER,
     9, RC_CRATERIA_EAST_BALLSPARK,
    14, RC_CRATERIA_STATUE_WATER,
};

const u8 sRoomItemsChozodia[] = {
    10, RC_CHOZODIA_CEILING_NEAR_MAP_STATION,
    14, RC_CHOZODIA_BEHIND_WORKBOT,
    24, RC_CHOZODIA_LEFT_OF_GLASS_TUBE,
    26, RC_CHOZODIA_TRIPLE_CRAWLING_PIRATES,
    34, RC_CHOZODIA_UPPER_CRATERIA_DOOR,
    41, RC_CHOZODIA_CHOZO_GHOST_AREA_MORPH_TUNNEL_ABOVE_WATER,
    41, RC_CHOZODIA_CHOZO_GHOST_AREA_UNDERWATER,
    47, RC_CHOZODIA_ORIGINAL_POWER_BOMB,
    49, RC_CHOZODIA_NEXT_TO_ORIGINAL_POWER_BOMB,
    54, RC_CHOZODIA_LAVA_DIVE,
    65, RC_CHOZODIA_ZOOMER_MAZE,
    66, RC_CHOZODIA_BOMB_MAZE,
    71, RC_CHOZODIA_UNDER_MECHA_RIDLEY_HALLWAY,
    73, RC_CHOZODIA_PIRATE_PITFALL_TRAP,
    78, RC_CHOZODIA_CHOZO_GHOST_AREA_LONG_SHINESPARK,
    87, RC_CHOZODIA_SE_CORNER_IN_HULL,
    89, RC_CHOZODIA_EAST_OF_UPPER_CRATERIA_DOOR,
    90, RC_CHOZODIA_CHOZO_GHOST_AREA_MORPH_TUNNEL_ABOVE_WATER,
    90, RC_CHOZODIA_CHOZO_GHOST_AREA_UNDERWATER,
    95, RC_CHOZODIA_RIGHT_OF_GLASS_TUBE,
};

const u8* const sRandoAreaItemLists[AREA_NORMAL_COUNT] = {
    [AREA_BRINSTAR] = sRoomItemsBrinstar,
    [AREA_KRAID] = sRoomItemsKraid,
    [AREA_NORFAIR] = sRoomItemsNorfair,
    [AREA_RIDLEY] = sRoomItemsRidley,
    [AREA_TOURIAN] = sRoomItemsTourian,
    [AREA_CRATERIA] = sRoomItemsCrateria,
    [AREA_CHOZODIA] = sRoomItemsChozodia,
};

const u8 sRandoAreaItemListLengths[AREA_NORMAL_COUNT] = {
    [AREA_BRINSTAR] = ARRAY_SIZE(sRoomItemsBrinstar),
    [AREA_KRAID] = ARRAY_SIZE(sRoomItemsKraid),
    [AREA_NORFAIR] = ARRAY_SIZE(sRoomItemsNorfair),
    [AREA_RIDLEY] = ARRAY_SIZE(sRoomItemsRidley),
    [AREA_TOURIAN] = ARRAY_SIZE(sRoomItemsTourian),
    [AREA_CRATERIA] = ARRAY_SIZE(sRoomItemsCrateria),
    [AREA_CHOZODIA] = ARRAY_SIZE(sRoomItemsChozodia),
};

const u8 sRandoItemToTankTilemap[RANDO_ITEM_END] = {
    [RANDO_ITEM_NONE] = 0,
    [RANDO_ITEM_ENERGY_TANKS] = 0x45,
    [RANDO_ITEM_MISSILES] = 0x41,
    [RANDO_ITEM_SUPER_MISSILES] = 0x4D,
    [RANDO_ITEM_POWER_BOMBS] = 0x49,
    [RANDO_ITEM_BEAM_BOMBS] = 0,
    [RANDO_ITEM_SUIT_MISC] = 0,
    [RANDO_ITEM_CUSTOM] = 0,
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
    /*  0 */ 13, 14,
    /*  1 */ 6, 7,
    /*  2 */ 9, 14,
    /*  3 */ 9, 14,
    /*  4 */ 10, 11,
    /*  5 */ 6, 7,
    /*  6 */ 6, 8,
    /*  7 */ 7, 8,
    /*  8 */ 7, 8,
    /*  9 */ 7, 8,
    /* 10 */ 10, 11,
    /* 11 */ 11, 12,
    /* 12 */ 8, 10,
    /* 13 */ 6, UCHAR_MAX,
    /* 14 */ 14, UCHAR_MAX,
    /* 15 */ 4, 10,
    /* 16 */ 10, 11,
    /* 17 */ 7, 8,
    /* 18 */ 6, 7,
    /* 19 */ 8, 12,
    /* 20 */ 7, 8,
    /* 21 */ 12, 13,
    /* 22 */ 13, 14,
    /* 23 */ 8, 13,
    /* 24 */ 3, 10,
    /* 25 */ 7, 8,
    /* 26 */ 3, 8,
    /* 27 */ 11, 13,
    /* 28 */ 3, 14,
    /* 29 */ 8, 11,
    /* 30 */ 8, UCHAR_MAX,
    /* 31 */ 9, 14,
    /* 32 */ 9, 14,
    /* 33 */ 10, 11,
    /* 34 */ 7, 8,
    /* 35 */ 3, 12,
    /* 36 */ 3, 10,
    /* 37 */ 8, 10,
    /* 38 */ 7, 10,
    /* 39 */ 10, 11,
    /* 40 */ 3, 11,
    /* 41 */ 3, 11,
    /* 42 */ 3, 6,
    /* 43 */ 3, 14,
    /* 44 */ 3, 14,
    /* 45 */ 3, 14,
    /* 46 */ 3, 9,
    /* 47 */ 4, 14,
    /* 48 */ 10, 13,
    /* 49 */ 13, 14,
    /* 50 */ UCHAR_MAX, UCHAR_MAX,
    /* 51 */ 8, 10,
    /* 52 */ 3, UCHAR_MAX,
    /* 53 */ 11, 12,
    /* 54 */ 10, 11,
    /* 55 */ 3, UCHAR_MAX,
    /* 56 */ 3, 13,
    /* 57 */ 3, UCHAR_MAX,
    /* 58 */ 3, UCHAR_MAX,
    /* 59 */ 3, UCHAR_MAX,
    /* 60 */ 3, 10,
    /* 61 */ 6, 11,
    /* 62 */ 11, 12,
    /* 63 */ 4, 14,
    /* 64 */ 6, 10,
    /* 65 */ 3, 8,
    /* 66 */ 4, 5,
    /* 67 */ 11, 12,
    /* 68 */ 8, 14,
    /* 69 */ 3, 8,
    /* 70 */ 13, 14,
    /* 71 */ 11, UCHAR_MAX,
    /* 72 */ 9, 10,
    /* 73 */ 9, 14,
    /* 74 */ 3, UCHAR_MAX,
    /* 75 */ 9, 11,
    /* 76 */ 3, 7,
    /* 77 */ 3, 7,
    /* 78 */ 3, 6,
};

const u16 sRevealedBlockTilemapValues[MAX_AMOUNT_OF_BLOCKS] = {
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SHOT_BLOCK_NEVER_REFORM)]              = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_TOP_LEFT_SHOT_BLOCK_NEVER_REFORM)]     = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_TOP_RIGHT_SHOT_BLOCK_NEVER_REFORM)]    = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_BOTTOM_LEFT_SHOT_BLOCK_NEVER_REFORM)]  = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_BOTTOM_RIGHT_SHOT_BLOCK_NEVER_REFORM)] = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SHOT_BLOCK_NO_REFORM)]                 = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_TOP_LEFT_SHOT_BLOCK_NO_REFORM)]        = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_TOP_RIGHT_SHOT_BLOCK_NO_REFORM)]       = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_BOTTOM_LEFT_SHOT_BLOCK_NO_REFORM)]     = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_BOTTOM_RIGHT_SHOT_BLOCK_NO_REFORM)]    = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SHOT_BLOCK_REFORM)]                    = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_BOMB_BLOCK_NEVER_REFORM)]              = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_BOMB_NEVER_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_BOMB_BLOCK_REFORM)]                    = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_BOMB_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_MISSILE_BLOCK_NEVER_REFORM)]           = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_MISSILE_NEVER_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_MISSILE_BLOCK_NO_REFORM)]              = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_MISSILE_NO_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SUPER_MISSILE_BLOCK_NEVER_REFORM)]     = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SUPER_MISSILE_NEVER_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SUPER_MISSILE_BLOCK_NO_REFORM)]        = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SUPER_MISSILE_NO_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SPEEDBOOST_BLOCK_NO_REFORM)]           = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SPEEDBOOST_NO_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SPEEDBOOST_BLOCK_REFORM)]              = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SPEEDBOOST_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_CRUMBLE_BLOCK)]                        = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_CRUMBLE,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_POWER_BOMB_BLOCK_NEVER_REFORM)]        = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_POWER_BOMB_NEVER_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SCREW_ATTACK_BLOCK_NO_REFORM)]         = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SCREW_ATTACK_NO_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_VERTICAL_BOMB_CHAIN1)]                 = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_VERTICAL_BOMB_CHAIN1,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_VERTICAL_BOMB_CHAIN2)]                 = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_VERTICAL_BOMB_CHAIN2,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_VERTICAL_BOMB_CHAIN3)]                 = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_VERTICAL_BOMB_CHAIN3,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_VERTICAL_BOMB_CHAIN4)]                 = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_VERTICAL_BOMB_CHAIN4,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HORIZONTAL_BOMB_CHAIN1)]               = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_HORIZONTAL_BOMB_CHAIN1,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HORIZONTAL_BOMB_CHAIN2)]               = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_HORIZONTAL_BOMB_CHAIN2,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HORIZONTAL_BOMB_CHAIN3)]               = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_HORIZONTAL_BOMB_CHAIN3,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HORIZONTAL_BOMB_CHAIN4)]               = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_HORIZONTAL_BOMB_CHAIN4,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SLOW_CRUMBLE_BLOCK)]                   = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SLOW_CRUMBLE,
    // Empty space, 31-35 (5 blocks)
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HIDDEN_ENERGY_TANK)]                   = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HIDDEN_MISSILE_TANK)]                  = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HIDDEN_SUPER_MISSILE_TANK)]            = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_HIDDEN_POWER_BOMB_TANK)]               = CLIPDATA_TILEMAP_FLAG | CLIPDATA_TILEMAP_SHOT_BLOCK_REFORM,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_ENERGY_TANK)]                          = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_MISSILE_TANK)]                         = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_SUPER_MISSILE_TANK)]                   = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_POWER_BOMB_TANK)]                      = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_UNDERWATER_ENERGY_TANK)]               = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_UNDERWATER_MISSILE_TANK)]              = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_UNDERWATER_SUPER_MISSILE_TANK)]        = 0,
    [BEHAVIOR_TO_BLOCK(CLIP_BEHAVIOR_UNDERWATER_POWER_BOMB_TANK)]           = 0,
};

const u8 sRandoStatusScreenData[RANDO_ABILITY_GROUP_COUNT][3] = {
    [RANDO_ABILITY_GROUP_CURRENT_DNA] = {2, 13, 14},
    [RANDO_ABILITY_GROUP_REQUIRED_DNA] = {2, 16, 17},
};

const u16 sRandoText_MetroidDNAAcquired[] = INCTEXT("{WIDTH(53)}{COLOR(5)}Metroid DNA acquired.\n{WIDTH(47)}Collect ?? more samples.");
const u16 sRandoText_MetroidDNAAcquired1Remaining[] = INCTEXT("{WIDTH(53)}{COLOR(5)}Metroid DNA acquired.\n{WIDTH(52)}Collect 1 more sample.");
const u16 sRandoText_AllMetroidDNAAcquired[] = INCTEXT("{WIDTH(14)}{COLOR(5)}All necessary Metroid DNA acquired.\n{WIDTH(31)}Mecha Ridley's door unlocked.");
