#ifndef RANDO_DATA_H
#define RANDO_DATA_H

#include "types.h"

#include "constants/rando.h"

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

#endif // RANDO_DATA_H
