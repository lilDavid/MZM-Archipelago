#include "rando_item.h"
#include "gba.h"
#include "macros.h"
#include "in_game_cutscene.h"

#include "constants/animated_graphics.h"
#include "constants/clipdata.h"
#include "constants/in_game_cutscene.h"
#include "constants/menus/pause_screen.h"
#include "constants/escape.h"
#include "constants/samus.h"
#include "constants/sprite.h"
#include "constants/text.h"

#include "data/block_data.h"
#include "data/text_data.h"
#include "data/text_pointers.h"
#include "data/rando_data.h"

#include "structs/animated_graphics.h"
#include "structs/bg_clip.h"
#include "structs/escape.h"
#include "structs/game_state.h"
#include "structs/rando.h"
#include "structs/room.h"
#include "structs/samus.h"
#include "structs/sprite.h"
#include "structs/text.h"


static u32 TextFindCharacter(const u16* str, u16 terminator) {
    u32 i = 0;
    while (str[i] != terminator)
        i += 1;
    return i;
}

static u32 TextCopyUntilCharacter(const u16* src, u16* dst, u16 terminator) {
    const u16* start = src;
    while (*src != terminator) {
        *dst = *src;
        dst++;
        src++;
    }
    return src - start;
}

static u32 TextGetStringWidth(const u16* str, u32 length) {
    u32 i;
    u32 textWidth = 0;
    for (i = 0; i < length; i++)
        textWidth += TextGetCharacterWidth(str[i]);

    return textWidth;
}

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
}

static u32 RandoCopyMessage(const struct RandoMessage* pMessage) {
    gCurrentRandoMessage = *pMessage;
    switch (pMessage->messageID) {
        case ITEM_ACQUISITION_MISSILES:
            if (gEquipment.maxMissiles == 0) {
                gCurrentRandoMessage.messageID = MESSAGE_MISSILE_TANK_ACQUIRED;
                gCurrentRandoMessage.oneLine = FALSE;
            }
            break;
        case ITEM_ACQUISITION_SUPER_MISSILES:
            if (gEquipment.maxSuperMissiles == 0) {
                gCurrentRandoMessage.messageID = MESSAGE_SUPER_MISSILE_TANK_ACQUIRED;
                gCurrentRandoMessage.oneLine = FALSE;
            }
            break;
        case ITEM_ACQUISITION_POWER_BOMB:
            if (gEquipment.maxPowerBombs == 0) {
                gCurrentRandoMessage.messageID = MESSAGE_POWER_BOMB_TANK_ACQUIRED;
                gCurrentRandoMessage.oneLine = FALSE;
            }
            break;
    }
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
        case RANDO_ITEM_BEAM_BOMBS:
            gEquipment.beamBombs |= item->value;
            break;
        case RANDO_ITEM_SUIT_MISC:
            gEquipment.suitMisc |= item->value;
            break;
    }
}

void RandoActivateAcquiredItem(void) {
    switch (gCurrentItemBeingAcquired) {
        case ITEM_ACQUISITION_LONG_BEAM:
            gEquipment.beamBombsActivation |= BBF_LONG_BEAM;
            ProjectileCallLoadGraphicsAndClearProjectiles();
            break;
        case ITEM_ACQUISITION_CHARGE_BEAM:
            gEquipment.beamBombsActivation |= BBF_CHARGE_BEAM;
            break;
        case ITEM_ACQUISITION_ICE_BEAM:
            gEquipment.beamBombsActivation |= BBF_ICE_BEAM;
            ProjectileCallLoadGraphicsAndClearProjectiles();
            break;
        case ITEM_ACQUISITION_WAVE_BEAM:
            gEquipment.beamBombsActivation |= BBF_WAVE_BEAM;
            ProjectileCallLoadGraphicsAndClearProjectiles();
            break;
        case ITEM_ACQUISITION_PLASMA_BEAM:
            if (UNKNOWN_ITEMS_ARE_USABLE) {
                gEquipment.beamBombsActivation |= BBF_PLASMA_BEAM;
                ProjectileCallLoadGraphicsAndClearProjectiles();
            }
            break;
        case ITEM_ACQUISITION_BOMBS:
            if (gEquipment.suitMiscActivation & SMF_MORPH_BALL)
                gEquipment.beamBombsActivation |= BBF_BOMBS;
            break;
        case ITEM_ACQUISITION_VARIA:
            gEquipment.suitMiscActivation |= SMF_VARIA_SUIT;
            if (UNKNOWN_ITEMS_ARE_USABLE)
                gEquipment.suitType = SUIT_FULLY_POWERED;
            break;
        case ITEM_ACQUISITION_GRAVITY:
            if (UNKNOWN_ITEMS_ARE_USABLE) {
                gEquipment.suitMiscActivation |= SMF_GRAVITY_SUIT;
                gEquipment.suitType = SUIT_FULLY_POWERED;
            }
            break;
        case ITEM_ACQUISITION_MORPH_BALL:
            gEquipment.suitMiscActivation |= SMF_MORPH_BALL;
            if (gEquipment.beamBombs & BBF_BOMBS)
                gEquipment.beamBombsActivation |= BBF_BOMBS;
            break;
        case ITEM_ACQUISITION_SPEEDBOOSTER:
            gEquipment.suitMiscActivation |= SMF_SPEEDBOOSTER;
            break;
        case ITEM_ACQUISITION_HIGH_JUMP:
            gEquipment.suitMiscActivation |= SMF_HIGH_JUMP;
            break;
        case ITEM_ACQUISITION_SCREW_ATTACK:
            gEquipment.suitMiscActivation |= SMF_SCREW_ATTACK;
            break;
        case ITEM_ACQUISITION_SPACE_JUMP:
            if (UNKNOWN_ITEMS_ARE_USABLE)
                gEquipment.suitMiscActivation |= SMF_SPACE_JUMP;
            break;
        case ITEM_ACQUISITION_POWER_GRIP:
            gEquipment.suitMiscActivation |= SMF_POWER_GRIP;
            break;
    }
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
    RandoCopyMessage(&placement->message);

    RandoGiveItem(&placement->item);

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, messageID, 6, gSamusData.yPosition, gSamusData.xPosition, 0);
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

static u32 RandoCanReceiveMultiworld() {
    int i, j;
    u32 dangerousSpriteset;

    // Disallowed states
    if (gGameModeSub1 != SUB_GAME_MODE_PLAYING ||
        gIncomingItem.itemType == RANDO_ITEM_NONE || gCurrentRandoMessage.data == NULL ||
        gEquipment.suitType == SUIT_SUITLESS ||
        gPreventMovementTimer || gDisablePause || gPauseScreenFlag || gShipLandingFlag)
        return FALSE;

    // Certain samus actions can affect the message banner
    for (i = 0; i < ARRAY_SIZE(sRandoDisallowedSamusPoses); i++) {
        if (sRandoDisallowedSamusPoses[i] == gSamusData.pose)
            return FALSE;
    }

    // Wait for area banner to disappear or boss to die
    for (i = 0; i < MAX_AMOUNT_OF_SPRITES; i++) {
        for (j = 0; j < ARRAY_SIZE(sRandoDisallowedExistingSprites); j++)
        if (gSpriteData[i].spriteId == sRandoDisallowedExistingSprites[j] && gSpriteData[i].status & SPRITE_STATUS_EXISTS)
            return FALSE;
    }

    // If the banner is already loaded, no need to worry about loading it
    for (i = 0; i < MAX_AMOUNT_OF_SPRITE_TYPES; i++) {
        if (gSpritesetSpritesID[i] == PSPRITE_ITEM_BANNER)
            return TRUE;
    }

    // If banner isn't already loaded, gfx will overwrite the timer
    if (gCurrentEscapeStatus != ESCAPE_STATUS_NONE)
        return FALSE;

    // If being chased, message will overwrite pirate graphics
    if (gAlarmTimer) {
        for (i = 0; i < ARRAY_SIZE(sRandoChozodiaSaveAndMapRooms); i++) {
            if (sRandoChozodiaSaveAndMapRooms[i] == gCurrentRoom)
                return FALSE;
        }
    }

    // Message banner could overwrite graphics of certain sprites
    dangerousSpriteset = FALSE;
    for (i = 0; i < ARRAY_SIZE(sRandoMultiworldDangerousSpritesets); i++) {
        if (sRandoMultiworldDangerousSpritesets[i] == gSpriteset) {
            dangerousSpriteset = TRUE;
            break;
        }
    }
    if (!dangerousSpriteset)
        return TRUE;
    for (i = 0; i < ARRAY_SIZE(sRandoMultiworldDangerousRooms); i++) {
        if (sRandoMultiworldDangerousRooms[i][0] == gCurrentArea &&
            sRandoMultiworldDangerousRooms[i][1] == gCurrentRoom)
            return FALSE;
    }

    return TRUE;
}

u32 RandoHandleMultiworld() {
    if (!RandoCanReceiveMultiworld())
        return FALSE;

    gPreventMovementTimer = SAMUS_ITEM_PMT;
    RandoCopyMessage(&gIncomingMessage);
    gReceivingFromMultiworld = TRUE;

    // (Hopefully) fix the bug where the item acquisition freezes Samus in place instead of showing the message
    if (SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, MESSAGE_DUMMY, 6, gSamusData.yPosition, gSamusData.xPosition, 0) == UCHAR_MAX) {
        gPreventMovementTimer = 0;
        gReceivingFromMultiworld = FALSE;
        return FALSE;
    }

    RandoGiveItem(&gIncomingItem);
    return TRUE;
}
