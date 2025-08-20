#ifndef RANDO_STRUCT_H
#define RANDO_STRUCT_H

#include "types.h"

#include "constants/connection.h"
#include "constants/rando.h"

#include "structs/scroll.h"

// Structs

struct Seed {
    u8 playerName[64];
    u8 seedName[64];

    struct {
        u8 difficulties;

        u8 removeGravityHeatResistance;
        u8 usePowerBombsWithoutBomb;
        u8 buffPowerBombDrops;
        u8 separateHiJumpSpringBall;

        u8 skipChozodiaStealth;
        u8 startWithMaps;

        u8 revealMaps;
        u8 revealHiddenBlocks;
        u8 skipTourianOpening;
        u8 elevatorSpeed;
    } options;
};

struct RandoItem {
    u8 itemType;
    u8 waitForMessage;
    u16 value;  // Count for capacity upgrades, bit flag for major items
};

struct RandoSprite {
    const u8* gfx;
    const u16* pal;
};

struct RandoMessage {
    const u16* data;
    u16 soundEffect;
    u8 messageID;  // Treat this message *as if* it was the one with this ID
    u8 oneLine;
};

struct PlacedItem {
    struct RandoItem item;
    const struct RandoSprite* sprite;
    struct RandoMessage message;
};

struct StartingInventory {
    u8 energyTanks;
    u16 missileTanks;
    u8 superMissileTanks;
    u8 powerBombTanks;
    u8 beamBombs;
    u8 suitMisc;
    u8 customItems;
};

struct StartingSamusData {
    u16 xPosition;
    u16 yPosition;
    u8 timer;
    u8 standingStatus;
};

struct StartingLocationData {
    struct StartingSamusData samus;
    struct Camera camera;
    u8 area;
    u8 room;
    u8 lastDoorUsed;
    u8 useMotherShipDoors;
};

// Globals

extern const struct Seed sRandoSeed;
extern const struct PlacedItem sPlacedItems[RC_COUNT];
extern const struct StartingInventory sRandoStartingInventory;

extern struct RandoItem gIncomingItem;
extern struct RandoMessage gIncomingMessage;
extern u8 gIgnoreLocalItems;
extern u8 gCollectingLocation;
extern u16 gMultiworldItemCount;
extern u32 gRandoLocationBitfields[AREA_NORMAL_COUNT];

extern u8 gWarpToStart;

extern struct RandoMessage gCurrentRandoMessage;
extern u16 gDynamicMessageBuffer[160];

#endif /* RANDO_STRUCT_H */
