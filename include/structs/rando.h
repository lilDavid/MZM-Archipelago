#ifndef RANDO_STRUCT_H
#define RANDO_STRUCT_H

#include "types.h"

#include "constants/connection.h"
#include "constants/rando.h"

#include "structs/bg_clip.h"

// Structs

struct Seed {
    u16 playerNumber;
    u8 playerName[64];
    u8 seedName[64];

    struct {
        u8 unknownItemsAlwaysUsable;
        u8 skipChozodiaStealth;
        u8 usePowerBombsWithoutBomb;
        u8 removeGravityHeatResistance;
    } options;
};

struct StartingInventory {
    u8 energyTanks;
    u16 missileTanks;
    u8 superMissileTanks;
    u8 powerBombTanks;
    u8 beamBombs;
    u8 suitMisc;
};

struct PlacedItem {
    const u16* playerName;
    const u16* itemName;  // If null, use name determined by item ID
    u8 itemId;
};

// Globals

extern const struct Seed sRandoSeed;
extern const struct PlacedItem sPlacedItems[RC_MAX];
extern const struct StartingInventory sRandoStartingInventory;

extern const u8 sItemMessages[ITEM_MAX];
extern const u8 sRegionLocationOffsets[AREA_CHOZODIA + 2];
extern const struct ItemInfo sItemLocations[RC_MAX];

extern u8 gIncomingItemId;
extern u8 gReceivingFromMultiworld;
extern u8 gMultiworldItemCount;
extern u16 gMultiworldItemSenderName[2 * 16 + sizeof(" ()")];
extern u32 gRandoLocationBitfields[AREA_NORMAL_END + 1];

#endif /* RANDO_STRUCT_H */
