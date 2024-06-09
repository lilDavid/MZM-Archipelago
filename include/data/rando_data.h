#ifndef RANDO_DATA_H
#define RANDO_DATA_H

#include "types.h"

#include "constants/rando.h"


#define RANDO_GRAPHICS_SIZE 512

struct ItemGraphicsInfo {
    const u8* gfx;
    const u16* palette;
};

extern const struct ItemGraphicsInfo sItemGfxPointers[ITEM_MAX];

#endif // RANDO_DATA_H
