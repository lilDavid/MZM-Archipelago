#ifndef RANDO_DATA_H
#define RANDO_DATA_H

#include "types.h"

#include "constants/connection.h"
#include "constants/rando.h"
#include "constants/text.h"

#include "structs/bg_clip.h"
#include "structs/scroll.h"


#define RANDO_GRAPHICS_SIZE 512

struct ItemGraphicsInfo {
    const u8* gfx;
    const u16* palette;
};

extern const struct ItemGraphicsInfo sItemGfxPointers[ITEM_MAX];

extern const struct Camera sStartingLocationCamera;

extern const u8 sRandoMultiworldDangerousSpritesets[16];
extern const u8 sRandoMultiworldDangerousRooms[18][2];
extern const u8 sRandoChozodiaSaveAndMapRooms[8];
extern const u8 sRandoDisallowedSamusPoses[4];

extern const u8 sItemMessages[ITEM_MAX];
extern const u16 sRandoItemAcquisitionSfx[MESSAGE_DYNAMIC_ITEM];
extern const u8 sRegionLocationOffsets[AREA_CHOZODIA + 2];

extern const u8* const sRandoAreaItemLists[AREA_NORMAL_COUNT];
extern const u8 sRandoAreaItemListLengths[AREA_NORMAL_COUNT];
extern const u8 sRandoItemToTankTilemap[4];
extern const u8 sRandoAnimatedTileGaps[8];
extern const u8 sRandoPaletteSlots[79 * 2];

#endif // RANDO_DATA_H
