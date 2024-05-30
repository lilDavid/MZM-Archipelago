#ifndef RANDO_STRUCT_H
#define RANDO_STRUCT_H

#include "types.h"

// Structs

struct Seed {
    u16 playerNumber;
    u8 playerName[64];
    u8 seedName[64];
};

struct PlacedItem {
    u16* playerName;
    u16* itemName;  // If null, use name determined by item ID
    u8 itemId;
};

// Globals

extern const struct Seed sRandoSeed;
extern const struct PlacedItem sPlacedItems[100];

#endif /* RANDO_STRUCT_H */
