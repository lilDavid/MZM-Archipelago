#ifndef RANDO_DATA_H
#define RANDO_DATA_H

#include "types.h"

#include "constants/rando.h"


struct ItemGraphicsInfo {
    const u32* gfx;
    const u16* palette;
};

extern const struct ItemGraphicsInfo sItemGfxPointers[ITEM_MAX];

#endif // RANDO_DATA_H
