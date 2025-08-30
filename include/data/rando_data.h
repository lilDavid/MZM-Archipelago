#ifndef RANDO_DATA_H
#define RANDO_DATA_H

#include "types.h"

#include "constants/connection.h"
#include "constants/rando.h"
#include "constants/text.h"

#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/scroll.h"


extern const struct RandoItem sEmptyIncomingItem;
extern const struct RandoMessage sEmptyRandoMessage;

extern const struct StartingLocationData sStartingLocation;

extern const u8 sRandoMultiworldDangerousSpritesets[16];
extern const u8 sRandoMultiworldDangerousRooms[15][2];
extern const u8 sRandoDisallowedExistingSprites[5];
extern const u8 sRandoChozodiaSaveAndMapRooms[8];
extern const u8 sRandoDisallowedSamusPoses[4];

extern const u8 sRegionLocationOffsets[AREA_CHOZODIA + 2];

extern const u8* const sRandoAreaItemLists[AREA_NORMAL_COUNT];
extern const u8 sRandoAreaItemListLengths[AREA_NORMAL_COUNT];
extern const u8 sRandoItemToTankTilemap[RANDO_ITEM_END];
extern const u8 sRandoAnimatedTileGaps[8];
extern const u8 sRandoPaletteSlots[79 * 2];

extern const u16 sRevealedBlockTilemapValues[MAX_AMOUNT_OF_BLOCKS];

extern const u16 sRandoText_MetroidDNAAcquired[];
extern const u16 sRandoText_MetroidDNAAcquired1Remaining[];
extern const u16 sRandoText_AllMetroidDNAAcquired[];

extern const u8 sRandoStatusScreenData[RANDO_ABILITY_GROUP_COUNT][3];

#endif // RANDO_DATA_H
