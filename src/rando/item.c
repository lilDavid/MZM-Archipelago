#include "rando/item.h"

#include "gba.h"
#include "macros.h"

#include "constants/audio.h"
#include "constants/clipdata.h"
#include "constants/demo.h"
#include "constants/menus/pause_screen.h"
#include "constants/samus.h"
#include "constants/sprite.h"

#include "data/block_data.h"
#include "data/text_pointers.h"
#include "data/rando_data.h"

#include "structs/demo.h"
#include "structs/game_state.h"
#include "structs/rando.h"
#include "structs/room.h"
#include "structs/samus.h"
#include "structs/sprite.h"
#include "structs/text.h"


static u32 RandoGetRegion(u32 location) {
    if (location < RC_BRINSTAR_MAX)
        return AREA_BRINSTAR;
    if (location < RC_KRAID_MAX)
        return AREA_KRAID;
    if (location < RC_NORFAIR_MAX)
        return AREA_NORFAIR;
    if (location < RC_RIDLEY_MAX)
        return AREA_RIDLEY;
    if (location < RC_TOURIAN_MAX)
        return AREA_TOURIAN;
    if (location < RC_CRATERIA_MAX)
        return AREA_CRATERIA;
    if (location < RC_CHOZODIA_MAX)
        return AREA_CHOZODIA;
    return AREA_NONE;
}

static u32 RandoGetRegionFlag(u32 location, u32 region) {
    u32 offset;

    if (region == AREA_NONE)
        return 0;
    offset = sRegionLocationOffsets[region];
    location -= offset;
    return 1 << location;
}

u32 RandoIsLocationChecked(u32 location) {
    u32 region;
    u32 flag;

    region = RandoGetRegion(location);
    flag = RandoGetRegionFlag(location, region);

    return gRandoLocationBitfields[region] & flag;
}

static u32 RandoCheckLocation(u32 location) {
    u32 region;
    u32 flag;

    region = RandoGetRegion(location);
    flag = RandoGetRegionFlag(location, region);

    gRandoLocationBitfields[region] |= flag;

    gCollectingLocation = location;
}

void RandoGiveItem(const struct RandoItem* item) {
    switch (item->itemType) {
        case RANDO_ITEM_ENERGY_TANKS:
            gEquipment.maxEnergy = MIN(1299, gEquipment.maxEnergy + sTankIncreaseAmount[gDifficulty].energy * item->value);
            gEquipment.currentEnergy = gEquipment.maxEnergy;
            break;
        case RANDO_ITEM_MISSILES:
            gEquipment.maxMissiles = MIN(999, gEquipment.maxMissiles + sTankIncreaseAmount[gDifficulty].missile * item->value);
            gEquipment.currentMissiles = MIN(999, gEquipment.currentMissiles + sTankIncreaseAmount[gDifficulty].missile * item->value);
            break;
        case RANDO_ITEM_SUPER_MISSILES:
            gEquipment.maxSuperMissiles = MIN(99, gEquipment.maxSuperMissiles + sTankIncreaseAmount[gDifficulty].superMissile * item->value);
            gEquipment.currentSuperMissiles = MIN(99, gEquipment.currentSuperMissiles + sTankIncreaseAmount[gDifficulty].superMissile * item->value);
            break;
        case RANDO_ITEM_POWER_BOMBS:
            gEquipment.maxPowerBombs = MIN(99, gEquipment.maxPowerBombs + sTankIncreaseAmount[gDifficulty].powerBomb * item->value);
            gEquipment.currentPowerBombs = MIN(99, gEquipment.currentPowerBombs + sTankIncreaseAmount[gDifficulty].powerBomb * item->value);
            break;
        case RANDO_ITEM_METROID_DNA:
            gRandoEquipment.metroidDNA = MIN(99, gRandoEquipment.metroidDNA + item->value);
            if (gRandoEquipment.metroidDNA >= sRandoSeed.options.metroidDnaRequired)
                EventFunction(EVENT_ACTION_SETTING, EVENT_METROID_DNA_ACQUIRED);
            break;
        case RANDO_ITEM_BEAM_BOMBS:
            gEquipment.beamBombs |= item->value;
            break;
        case RANDO_ITEM_SUIT_MISC:
            gEquipment.suitMisc |= item->value;
            break;
        case RANDO_ITEM_CUSTOM:
            gRandoEquipment.customItems |= item->value;
            if (item->value == CIF_FULLY_POWERED_SUIT) {
                gEquipment.beamBombsActivation |= gEquipment.beamBombs & BBF_PLASMA_BEAM;
                ProjectileCallLoadGraphicsAndClearProjectiles();
                gEquipment.suitMiscActivation |= gEquipment.suitMisc & SMF_UNKNOWN_ITEMS;
                gEquipment.suitType = !!(gEquipment.suitMiscActivation & SMF_ALL_SUITS);
            }
            break;
    }
}

void RandoActivateItem(const struct RandoItem* item) {
    switch (item->itemType) {
        case RANDO_ITEM_BEAM_BOMBS:
            gEquipment.beamBombsActivation |= item->value;
            if (!(gRandoEquipment.customItems & CIF_FULLY_POWERED_SUIT))
                gEquipment.beamBombsActivation &= ~BBF_PLASMA_BEAM;
            if (!(gEquipment.suitMiscActivation & SMF_MORPH_BALL))
                gEquipment.beamBombsActivation &= ~BBF_BOMBS;
            if (item->value & (BBF_LONG_BEAM | BBF_ICE_BEAM | BBF_WAVE_BEAM | BBF_PLASMA_BEAM))
                ProjectileCallLoadGraphicsAndClearProjectiles();
            break;
        case RANDO_ITEM_SUIT_MISC:
            gEquipment.suitMiscActivation |= item->value;
            if (!(gRandoEquipment.customItems & CIF_FULLY_POWERED_SUIT))
                gEquipment.suitMiscActivation &= ~SMF_UNKNOWN_ITEMS;
            else if (gEquipment.suitMiscActivation & SMF_ALL_SUITS)
                gEquipment.suitType = SUIT_FULLY_POWERED;
            if (item->value & SMF_MORPH_BALL && gEquipment.beamBombs & BBF_BOMBS)
                gEquipment.beamBombsActivation |= BBF_BOMBS;
            break;
    }
}

void RandoActivateAcquiredItem(void) {
    struct RandoItem item;
    switch (gCurrentItemBeingAcquired) {
        case ITEM_ACQUISITION_LONG_BEAM:
        case ITEM_ACQUISITION_CHARGE_BEAM:
        case ITEM_ACQUISITION_ICE_BEAM:
        case ITEM_ACQUISITION_WAVE_BEAM:
        case ITEM_ACQUISITION_PLASMA_BEAM:
        case ITEM_ACQUISITION_BOMBS:
            item.itemType = RANDO_ITEM_BEAM_BOMBS;
            break;
        case ITEM_ACQUISITION_VARIA:
        case ITEM_ACQUISITION_GRAVITY:
        case ITEM_ACQUISITION_MORPH_BALL:
        case ITEM_ACQUISITION_SPEEDBOOSTER:
        case ITEM_ACQUISITION_HIGH_JUMP:
        case ITEM_ACQUISITION_SCREW_ATTACK:
        case ITEM_ACQUISITION_SPACE_JUMP:
        case ITEM_ACQUISITION_POWER_GRIP:
            item.itemType = RANDO_ITEM_SUIT_MISC;
            break;
    }
    switch (gCurrentItemBeingAcquired) {
        case ITEM_ACQUISITION_LONG_BEAM:
            item.value = BBF_LONG_BEAM;
            break;
        case ITEM_ACQUISITION_CHARGE_BEAM:
            item.value = BBF_CHARGE_BEAM;
            break;
        case ITEM_ACQUISITION_ICE_BEAM:
            item.value = BBF_ICE_BEAM;
            break;
        case ITEM_ACQUISITION_WAVE_BEAM:
            item.value = BBF_WAVE_BEAM;
            break;
        case ITEM_ACQUISITION_PLASMA_BEAM:
            item.value = BBF_PLASMA_BEAM;
            break;
        case ITEM_ACQUISITION_BOMBS:
            item.value = BBF_BOMBS;
            break;
        case ITEM_ACQUISITION_VARIA:
            item.value = SMF_VARIA_SUIT;
            break;
        case ITEM_ACQUISITION_GRAVITY:
            item.value = SMF_GRAVITY_SUIT;
            break;
        case ITEM_ACQUISITION_MORPH_BALL:
            item.value = SMF_MORPH_BALL;
            break;
        case ITEM_ACQUISITION_SPEEDBOOSTER:
            item.value = SMF_SPEEDBOOSTER;
            break;
        case ITEM_ACQUISITION_HIGH_JUMP:
            item.value = SMF_HIGH_JUMP;
            break;
        case ITEM_ACQUISITION_SCREW_ATTACK:
            item.value = SMF_SCREW_ATTACK;
            break;
        case ITEM_ACQUISITION_SPACE_JUMP:
            item.value = SMF_SPACE_JUMP;
            break;
        case ITEM_ACQUISITION_POWER_GRIP:
            item.value = SMF_POWER_GRIP;
            break;
    }
    RandoActivateItem(&item);
}

void RandoGiveItemFromCheck(u32 location) {
    const struct PlacedItem* placement;
    s32 messageID;
    u32 messageLength;
    u32 lineLength;
    u32 lineWidth;
    u16* pLine2;

    RandoCheckLocation(location);
    placement = &sPlacedItems[location];

    gPreventMovementTimer = SAMUS_ITEM_PMT;
    messageID = MESSAGE_DUMMY;
    gCurrentRandoMessage = placement->message;

    if (!gIgnoreLocalItems)
        RandoGiveItem(&placement->item);

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, messageID, 6, gSamusData.yPosition, gSamusData.xPosition, 0);
}

u32 RandoGetFinalCompletionPercentage(void) {
    u32 percentage;
    u32 mask;
    u32 i;

    // Count completion percentage as number of checked location bits
    // If extra bits are set, the percentage will be higher, but they shouldn't be set
    percentage = 0;
    for (i = AREA_BRINSTAR; i < AREA_NORMAL_COUNT; i++) {
        for (mask = 1; mask; mask <<= 1)
            if (gRandoLocationBitfields[i] & mask)
                percentage++;
    }

    // TODO: Refactor location IDs so we can count items but ignore extra checks
    if (RandoIsLocationChecked(RC_CHOZODIA_RUINS_TEST_REWARD))
        percentage--;

    return percentage;
}

void RandoPlaceItemInSpriteGraphics(u32 location, u32 row, u32 column, u32 palette, u32 frames) {
    void* pal;
    const struct PlacedItem* pItem;
    u32 i;
    u32 y;
    u32 start;

    start = 0;
    if (frames == 1)
        start = 1;

    pItem = &sPlacedItems[location];
    for (i = 0; i < frames; i++) {
        for (y = 0; y < 2; y++) {
            DmaTransfer(3, pItem->sprite->gfx + (0x80 * (start + i)) + (0x40 * y), VRAM_BASE + 0x14000 + (row * 0x800) + (y * 0x400) + ((column + i) * 0x40), 32 * 2, 32);
        }
    }

    if (gGameModeSub1 == SUB_GAME_MODE_DOOR_TRANSITION || gGameModeSub1 == SUB_GAME_MODE_LOADING_ROOM || location == RC_BRINSTAR_MORPH_BALL)
        pal = EWRAM_BASE + 0x35700;
    else
        pal = PALRAM_BASE + 0x300;
    DMA_SET(3, pItem->sprite->pal, pal + (palette * 16 * sizeof(u16)), C_32_2_16(DMA_ENABLE, 16));
}

u32 RandoGetItemMessageTime(void) {
    switch (gCurrentRandoMessage.soundEffect) {
        case MUSIC_GETTING_FULLY_POWERED_SUIT_JINGLE:
            return CONVERT_SECONDS(5.) + TWO_THIRD_SECOND;
        case MUSIC_GETTING_TANK_JINGLE:
            return CONVERT_SECONDS(1.) + TWO_THIRD_SECOND;
        default:
            return CONVERT_SECONDS(0.5);
    }
}

void RandoGiveStartingInventory(void) {
    gEquipment.currentEnergy = gEquipment.maxEnergy = MIN(1299, sStartingHealthAmmo.energy + sRandoStartingInventory.energyTanks * sTankIncreaseAmount[gDifficulty].energy);
    gEquipment.currentMissiles = gEquipment.maxMissiles = MIN(999, sStartingHealthAmmo.missile + sRandoStartingInventory.missileTanks * sTankIncreaseAmount[gDifficulty].missile);
    gEquipment.currentSuperMissiles = gEquipment.maxSuperMissiles = MIN(99, sStartingHealthAmmo.superMissile + sRandoStartingInventory.superMissileTanks * sTankIncreaseAmount[gDifficulty].superMissile);
    gEquipment.currentPowerBombs = gEquipment.maxPowerBombs = MIN(99, sStartingHealthAmmo.powerBomb + sRandoStartingInventory.powerBombTanks * sTankIncreaseAmount[gDifficulty].powerBomb);

    gEquipment.beamBombsActivation = gEquipment.beamBombs = sRandoStartingInventory.beamBombs;
    gEquipment.suitMiscActivation = gEquipment.suitMisc = sRandoStartingInventory.suitMisc;
    gRandoEquipment.customItems = sRandoStartingInventory.customItems;

    if (gRandoEquipment.customItems & CIF_FULLY_POWERED_SUIT) {
        gEquipment.suitType = !!(gEquipment.suitMisc & SMF_ALL_SUITS);
    } else {
        gEquipment.beamBombsActivation &= ~BBF_PLASMA_BEAM;
        gEquipment.suitMiscActivation &= ~SMF_UNKNOWN_ITEMS;
    }

    if (sRandoSeed.options.startWithMaps)
        gEquipment.downloadedMapStatus = (1 << AREA_NORMAL_COUNT) - 1;
}

u32 RandoCanSpringBall(void) {
    if (gRandoEquipment.customItems & CIF_SPRING_BALL) {
        return TRUE;
    }

    return !(sRandoSeed.options.separateHiJumpSpringBall || gDemoState == DEMO_STATE_PLAYING) &&
        (gEquipment.suitMisc & SMF_HIGH_JUMP);
}
