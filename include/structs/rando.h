#ifndef RANDO_STRUCT_H
#define RANDO_STRUCT_H

#include "types.h"

#include "constants/connection.h"
#include "constants/rando.h"

#include "structs/bg_clip.h"

// Structs

struct RandomizerOptions {
    u8 unknownItemsAlwaysUsable;
};

struct Seed {
    u16 playerNumber;
    u8 playerName[64];
    u8 seedName[64];

    struct RandomizerOptions options;
};

struct PlacedItem {
    const u16* playerName;
    const u16* itemName;  // If null, use name determined by item ID
    u8 itemId;
};

// Globals

extern const struct Seed sRandoSeed;
extern const struct PlacedItem sPlacedItems[RC_MAX];

extern const u8 sItemMessages[ITEM_MAX];
extern const u8 sRegionLocationOffsets[AREA_NORMAL_END + 1][2];  // Items are pairs: [start, end]
extern const struct ItemInfo sItemLocations[RC_MAX];

extern u32 gRandoLocationBitfields[AREA_NORMAL_END + 1];

#endif /* RANDO_STRUCT_H */
