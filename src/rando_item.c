#include "rando_item.h"
#include "event.h"
#include "gba.h"
#include "macros.h"
#include "in_game_cutscene.h"

#include "constants/animated_graphics.h"
#include "constants/in_game_cutscene.h"
#include "constants/menus/pause_screen.h"
#include "constants/escape.h"
#include "constants/event.h"
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

static u32 RandoGetLocationAtPosition(u32 area, u32 room, u32 xPosition, u32 yPosition) {
    u32 i;
    u32 end;
    const struct ItemInfo* location;

    end = sRegionLocationOffsets[area + 1];
    for (i = sRegionLocationOffsets[area]; i < end; i++) {
        location = &sItemLocations[i];
        if (location->room == gCurrentRoom && xPosition == location->xPosition && yPosition == location->yPosition) {
            return i;
        }
    }

    return RC_MAX;
}

u32 RandoGetItemAtPosition(u32 area, u32 room, u32 xPosition, u32 yPosition) {
    u32 location = RandoGetLocationAtPosition(area, room, xPosition, yPosition);
    if (location < RC_MAX)
        return sPlacedItems[location].itemId;
    return ITEM_NONE;
}

static u32 RandoGetItemMessage(u32 itemId) {
    s32 messageID;

    if (itemId >= ITEM_MAX)
        return MESSAGE_DUMMY;

    gPreventMovementTimer = SAMUS_ITEM_PMT;

    messageID = sItemMessages[itemId];
    switch (itemId) {
        case ITEM_MISSILE_TANK:
            messageID = (gEquipment.maxMissiles == 0) ? MESSAGE_FIRST_MISSILE_TANK : MESSAGE_MISSILE_TANK_ACQUIRED;
            break;
        case ITEM_SUPER_MISSILE_TANK:
            messageID = (gEquipment.maxSuperMissiles == 0) ? MESSAGE_FIRST_SUPER_MISSILE_TANK : MESSAGE_SUPER_MISSILE_TANK_ACQUIRED;
            break;
        case ITEM_POWER_BOMB_TANK:
            messageID = (gEquipment.maxPowerBombs == 0) ? MESSAGE_FIRST_POWER_BOMB_TANK : MESSAGE_POWER_BOMB_TANK_ACQUIRED;
            break;
        case ITEM_PLASMA_BEAM:
            if (!sRandoSeed.options.unknownItemsAlwaysUsable && gEquipment.suitType != SUIT_FULLY_POWERED)
                messageID = MESSAGE_UKNOWN_ITEM_PLASMA;
            break;
        case ITEM_GRAVITY_SUIT:
            if (!sRandoSeed.options.unknownItemsAlwaysUsable && gEquipment.suitType != SUIT_FULLY_POWERED)
                messageID = MESSAGE_UNKNOWN_ITEM_GRAVITY;
            break;
        case ITEM_SPACE_JUMP:
            if (!sRandoSeed.options.unknownItemsAlwaysUsable && gEquipment.suitType != SUIT_FULLY_POWERED)
                messageID = MESSAGE_UNKNOWN_ITEM_SPACE_JUMP;
            break;
    }
    return messageID;
}

static void RandoItemApply(u32 itemId) {
    switch (itemId) {
        case ITEM_ENERGY_TANK:
            gEquipment.maxEnergy = MIN(1299, gEquipment.maxEnergy + sTankIncreaseAmount[gDifficulty].energy);
            gEquipment.currentEnergy = gEquipment.maxEnergy;
            break;
        case ITEM_MISSILE_TANK:
            gEquipment.maxMissiles = MIN(999, gEquipment.maxMissiles + sTankIncreaseAmount[gDifficulty].missile);
            gEquipment.currentMissiles = MIN(999, gEquipment.currentMissiles + sTankIncreaseAmount[gDifficulty].missile);
            break;
        case ITEM_SUPER_MISSILE_TANK:
            gEquipment.maxSuperMissiles = MIN(99, gEquipment.maxSuperMissiles + sTankIncreaseAmount[gDifficulty].superMissile);
            gEquipment.currentSuperMissiles = MIN(99, gEquipment.currentSuperMissiles + sTankIncreaseAmount[gDifficulty].superMissile);
            break;
        case ITEM_POWER_BOMB_TANK:
            gEquipment.maxPowerBombs = MIN(99, gEquipment.maxPowerBombs + sTankIncreaseAmount[gDifficulty].powerBomb);
            gEquipment.currentPowerBombs = MIN(99, gEquipment.currentPowerBombs + sTankIncreaseAmount[gDifficulty].powerBomb);
            break;
        case ITEM_LONG_BEAM:
            gEquipment.beamBombs |= BBF_LONG_BEAM;
            break;
        case ITEM_CHARGE_BEAM:
            gEquipment.beamBombs |= BBF_CHARGE_BEAM;
            break;
        case ITEM_ICE_BEAM:
            gEquipment.beamBombs |= BBF_ICE_BEAM;
            break;
        case ITEM_WAVE_BEAM:
            gEquipment.beamBombs |= BBF_WAVE_BEAM;
            break;
        case ITEM_PLASMA_BEAM:
            gEquipment.beamBombs |= BBF_PLASMA_BEAM;
            break;
        case ITEM_BOMB:
            gEquipment.beamBombs |= BBF_BOMBS;
            break;
        case ITEM_VARIA_SUIT:
            gEquipment.suitMisc |= SMF_VARIA_SUIT;
            break;
        case ITEM_GRAVITY_SUIT:
            gEquipment.suitMisc |= SMF_GRAVITY_SUIT;
            break;
        case ITEM_MORPH_BALL:
            gEquipment.suitMisc |= SMF_MORPH_BALL;
            break;
        case ITEM_SPEED_BOOSTER:
            gEquipment.suitMisc |= SMF_SPEEDBOOSTER;
            break;
        case ITEM_HIJUMP_BOOTS:
            gEquipment.suitMisc |= SMF_HIGH_JUMP;
            break;
        case ITEM_SCREW_ATTACK:
            gEquipment.suitMisc |= SMF_SCREW_ATTACK;
            break;
        case ITEM_SPACE_JUMP:
            gEquipment.suitMisc |= SMF_SPACE_JUMP;
            break;
        case ITEM_POWER_GRIP:
            gEquipment.suitMisc |= SMF_POWER_GRIP;
            break;
    }
}

u32 RandoGiveItem(u32 itemId) {
    u32 messageId;

    messageId = RandoGetItemMessage(itemId);
    RandoItemApply(itemId);
    return messageId;
}

void RandoGiveItemFromPosition(u32 area, u32 room, u32 xPosition, u32 yPosition) {
    u32 messageLength;
    u32 lineLength;
    u32 lineWidth;

    u32 location = RandoGetLocationAtPosition(area, room, xPosition, yPosition);
    if (location < RC_MAX) {
        RandoGiveItemFromCheck(location);
        return;
    }

    // Create error message
    messageLength = TextCopyUntilCharacter(sEnglishText_Message_CheckFromPositionError,
                                           gDynamicMessageBuffer,
                                           CHAR_TERMINATOR);
    messageLength += TextCopyUntilCharacter(sLocationTextPointers[LANGUAGE_ENGLISH][gCurrentArea] + 1,
                                            gDynamicMessageBuffer + messageLength,
                                            CHAR_TERMINATOR);
    gDynamicMessageBuffer[messageLength++] = CHAR_EMPTY_SPACE;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (room / 10) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + room % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_EMPTY_SPACE;
    gDynamicMessageBuffer[messageLength++] = CHAR_OPENING_PARENTHESIS;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (xPosition / 100) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (xPosition / 10) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + xPosition % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_COMMA;
    gDynamicMessageBuffer[messageLength++] = CHAR_EMPTY_SPACE;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (yPosition / 100) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (yPosition / 10) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + yPosition % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_CLOSING_PARENTHESIS;
    gDynamicMessageBuffer[messageLength++] = CHAR_TERMINATOR;
    lineLength = TextFindCharacter(gDynamicMessageBuffer + 2, CHAR_NEW_LINE);
    lineLength = TextFindCharacter(gDynamicMessageBuffer + lineLength + 4, CHAR_TERMINATOR);
    lineWidth = TextGetStringWidth(gDynamicMessageBuffer + lineLength + 4, lineLength);
    gDynamicMessageBuffer[messageLength - lineLength - 2] = CHAR_WIDTH_MASK | (224 - lineWidth) / 2;

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, MESSAGE_DYNAMIC_ITEM, 6, gSamusData.yPosition, gSamusData.xPosition, 0);
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

    if (placement->playerName) {
        gPreventMovementTimer = SAMUS_ITEM_PMT;
        messageID = sItemMessages[placement->itemId];

        // Item name
        if (placement->itemName) {
            messageLength = TextCopyUntilCharacter(placement->itemName,
                                                    gDynamicMessageBuffer,
                                                    CHAR_TERMINATOR);
        } else {
            messageLength = TextCopyUntilCharacter(sMessageTextPointers[gLanguage][messageID],
                                                   gDynamicMessageBuffer,
                                                   CHAR_NEW_LINE);
        }
        gDynamicMessageBuffer[messageLength++] = CHAR_NEW_LINE;

        // "Sent to <player name>."
        pLine2 = gDynamicMessageBuffer + messageLength;
        messageLength++;
        messageLength += TextCopyUntilCharacter(sEnglishText_MessageFragment_Sent,
                                                gDynamicMessageBuffer + messageLength,
                                                CHAR_TERMINATOR);
        messageLength += TextCopyUntilCharacter(placement->playerName,
                                                gDynamicMessageBuffer + messageLength,
                                                CHAR_TERMINATOR);
        gDynamicMessageBuffer[messageLength++] = CHAR_DOT;
        gDynamicMessageBuffer[messageLength++] = CHAR_TERMINATOR;
        lineLength = TextFindCharacter(pLine2 + 2, CHAR_TERMINATOR);
        lineWidth = TextGetStringWidth(pLine2 + 2, lineLength);
        pLine2[0] = CHAR_WIDTH_MASK | (224 - lineWidth) / 2;

        messageID = MESSAGE_DYNAMIC_ITEM;
    } else {
        messageID = RandoGiveItem(placement->itemId);
    }

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, messageID, 6, gSamusData.yPosition, gSamusData.xPosition, 0);
}

void RandoPlaceItemInTileGraphics(u32 location) {
    u32 i;
    u32 j;
    u32 k;
    struct AnimatedGraphicsInfo* pGraphics;

    u32 item = sPlacedItems[location].itemId;
    for (pGraphics = gAnimatedGraphicsData, i = 0; i < ARRAY_SIZE(gAnimatedGraphicsData); i++, pGraphics++) {
        if (pGraphics->type == ANIMATED_GFX_TYPE_NONE) {
            pGraphics->type = ANIMATED_GFX_TYPE_NORMAL;
            pGraphics->framesPerState = 10;
            pGraphics->numberOfStates = 4;
            pGraphics->pGraphics = sItemGfxPointers[item].gfx;
            pGraphics->currentAnimationFrame = 0;
            pGraphics->animationDurationCounter = 0;
            pGraphics->graphicsEntry = ANIMATED_GFX_ID_RANDO + item;

            for (j = 0; j < 16; j++) {
                for (k = 2; k < 16; k++) {
                    if (((u16*) PALRAM_BASE)[16 * j + k] != ((u16*) PALRAM_BASE)[16 * j + 1])
                        break;
                }
                if (k >= 16)
                    break;
            }
            if (j >= 256)
                j = 15;  // Give up and use palette 15

            gCommonTilemap[4 * (0xD0 + i)] = 4 * i | (j << 12);
            gCommonTilemap[4 * (0xD0 + i) + 1] = 4 * i + 1 | (j << 12);
            gCommonTilemap[4 * (0xD0 + i) + 2] = 4 * i + 2 | (j << 12);
            gCommonTilemap[4 * (0xD0 + i) + 3] = 4 * i + 3 | (j << 12);

            DMA_SET(3, sItemGfxPointers[item].palette, PALRAM_BASE + (j * 16 * sizeof(u16)), C_32_2_16(DMA_ENABLE, 16));

            return;
        }
    }
}

u32 RandoGetTileEntry(u32 item) {
    u32 i;
    struct AnimatedGraphicsInfo* pGraphics;

    for (pGraphics = gAnimatedGraphicsData, i = 0; i < ARRAY_SIZE(gAnimatedGraphicsData); i++, pGraphics++) {
        if (pGraphics->graphicsEntry == ANIMATED_GFX_ID_RANDO + item)
            return 0xD0 + i;
    }

    return 0xD0;
}

void RandoPlaceItemInSpriteGraphics(u32 location, u32 row, u32 column, u32 palette, u32 frames) {
    void* pal;
    u32 i;
    u32 y;
    u32 start;
    u32 item;

    start = 0;
    if (frames == 1)
        start = 1;

    item = sPlacedItems[location].itemId;
    for (i = 0; i < frames; i++) {
        for (y = 0; y < 2; y++) {
            DmaTransfer(3, sItemGfxPointers[item].gfx + (0x80 * (start + i)) + (0x40 * y), VRAM_BASE + 0x14000 + (row * 0x800) + (y * 0x400) + ((column + i) * 0x40), 32 * 2, 32);
        }
    }

    if (gGameModeSub1 == SUB_GAME_MODE_DOOR_TRANSITION || gGameModeSub1 == SUB_GAME_MODE_LOADING_ROOM || location == RC_BRINSTAR_MORPH_BALL)
        pal = EWRAM_BASE + 0x35700;
    else
        pal = PALRAM_BASE + 0x300;
    DMA_SET(3, sItemGfxPointers[item].palette, pal + (palette * 16 * sizeof(u16)), C_32_2_16(DMA_ENABLE, 16));
}

static u32 RandoIsInDangerousPose() {
    u32 i;

    for (i = 0; i < ARRAY_SIZE(sRandoDisallowedSamusPoses); i++) {
        if (sRandoDisallowedSamusPoses[i] == gSamusData.pose)
            return TRUE;
    }
    return FALSE;
}

static u32 RandoIsInDangerousRoom() {
    u32 i;
    u32 dangerousSpriteset;

    if (gAlarmTimer) {
        for (i = 0; i < ARRAY_SIZE(sRandoChozodiaSaveAndMapRooms); i++) {
            if (sRandoChozodiaSaveAndMapRooms[i] == gCurrentRoom)
                return TRUE;
        }
    }

    dangerousSpriteset = FALSE;
    for (i = 0; i < ARRAY_SIZE(sRandoMultiworldDangerousSpritesets); i++) {
        if (sRandoMultiworldDangerousSpritesets[i] == gSpriteset) {
            dangerousSpriteset = TRUE;
            break;
        }
    }
    if (!dangerousSpriteset)
        return FALSE;

    for (i = 0; i < ARRAY_SIZE(sRandoMultiworldDangerousRooms); i++) {
        if (sRandoMultiworldDangerousRooms[i][0] == gCurrentArea &&
            sRandoMultiworldDangerousRooms[i][1] == gCurrentRoom)
            return TRUE;
    }
    return FALSE;
}

void RandoHandleMultiworld() {
    u32 sourceItemMessage;
    u32 messageId;
    u32 messageLength;
    u32 lineLength;
    u32 lineWidth;
    u16* pLine2;

    if (gGameModeSub1 != SUB_GAME_MODE_PLAYING ||                                              // Wrong game state
        gIncomingItemId >= ITEM_MAX ||                                                         // No item queued
        gEquipment.suitType == SUIT_SUITLESS || gCurrentEscapeStatus != ESCAPE_STATUS_NONE ||  // Stealth or escape
        gPreventMovementTimer || gDisablePause || gShipLandingFlag ||                          // Not controlling Samus
        (gSpriteData[0].spriteId == PSPRITE_AREA_BANNER && gSpriteData[0].status != 0) ||      // Showing area name
        RandoIsInDangerousPose() || RandoIsInDangerousRoom())                                  // Could cause weird visuals
        return;

    sourceItemMessage = gCurrentItemBeingAcquired = RandoGetItemMessage(gIncomingItemId);
    gReceivingFromMultiworld = TRUE;
    switch (gCurrentItemBeingAcquired) {
        case MESSAGE_PLASMA_BEAM:
            gCurrentItemBeingAcquired = ITEM_ACQUISITION_PLASMA_BEAM;
            messageId = MESSAGE_DYNAMIC_ITEM_MAJOR;
            break;
        case MESSAGE_GRAVITY_SUIT:
            gCurrentItemBeingAcquired = ITEM_ACQUISITION_GRAVITY;
            messageId = MESSAGE_DYNAMIC_ITEM_MAJOR;
            break;
        case MESSAGE_SPACE_JUMP:
            gCurrentItemBeingAcquired = ITEM_ACQUISITION_SPACE_JUMP;
            messageId = MESSAGE_DYNAMIC_ITEM_MAJOR;
            break;
        case MESSAGE_UKNOWN_ITEM_PLASMA:
        case MESSAGE_UNKNOWN_ITEM_GRAVITY:
        case MESSAGE_UNKNOWN_ITEM_SPACE_JUMP:
            messageId = MESSAGE_DYNAMIC_ITEM_UNKNOWN;
            break;
        case MESSAGE_ENERGY_TANK_ACQUIRED:
        case MESSAGE_MISSILE_TANK_ACQUIRED:
        case MESSAGE_SUPER_MISSILE_TANK_ACQUIRED:
        case MESSAGE_POWER_BOMB_TANK_ACQUIRED:
            messageId = MESSAGE_DYNAMIC_ITEM;
            break;
        case MESSAGE_DUMMY:
            gCurrentItemBeingAcquired = ITEM_ACQUISITION_PLASMA_BEAM;
            messageId = MESSAGE_DYNAMIC_ITEM;
            break;
        default:
            messageId = MESSAGE_DYNAMIC_ITEM_MAJOR;
            break;
    }

    // (Hopefully) fix the bug where the item acquisition freezes Samus in place instead of showing the message
    if (SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, messageId, 6, gSamusData.yPosition, gSamusData.xPosition, 0) == UCHAR_MAX) {
        gPreventMovementTimer = 0;
        return;
    }
    RandoItemApply(gIncomingItemId);

    // Item name
    messageLength = TextCopyUntilCharacter(sMessageTextPointers[gLanguage][sourceItemMessage],
                                           gDynamicMessageBuffer,
                                           CHAR_NEW_LINE);
    gDynamicMessageBuffer[messageLength++] = CHAR_NEW_LINE;

    // "Received from <player name>."
    pLine2 = gDynamicMessageBuffer + messageLength;
    messageLength++;
    messageLength += TextCopyUntilCharacter(sEnglishText_MessageFragment_Received,
                                            gDynamicMessageBuffer + messageLength,
                                            CHAR_TERMINATOR);
    messageLength += TextCopyUntilCharacter(gMultiworldItemSenderName,
                                            gDynamicMessageBuffer + messageLength,
                                            CHAR_TERMINATOR);
    gDynamicMessageBuffer[messageLength++] = CHAR_DOT;
    gDynamicMessageBuffer[messageLength++] = CHAR_TERMINATOR;
    lineLength = TextFindCharacter(pLine2 + 2, CHAR_TERMINATOR);
    lineWidth = TextGetStringWidth(pLine2 + 2, lineLength);
    pLine2[0] = CHAR_WIDTH_MASK | (224 - lineWidth) / 2;
}
