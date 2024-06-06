#include "rando_item.h"

#include "constants/samus.h"
#include "constants/sprite.h"
#include "constants/text.h"

#include "data/block_data.h"
#include "data/text_data.h"
#include "data/text_pointers.h"

#include "structs/bg_clip.h"
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

void RandoGiveItemFromPosition(u32 area, struct RoomEntry* pRoomEntry, u32 xPosition, u32 yPosition) {
    u32 itemX;
    u32 itemY;
    u32 i;
    u32 messageLength;
    u32 lineLength;
    u32 lineWidth;
    const struct TankLocation* location;

    itemX = (xPosition - 2) / 15 + pRoomEntry->mapX;
    itemY = (yPosition - 2) / 10 + pRoomEntry->mapY;

    for (i = 0; i < RC_MAX; i++) {
        location = &sLocationMapPositions[i];
        if (location->area == area && location->xPosition == itemX && location->yPosition == itemY) {
            RandoGiveItemFromCheck(i);
            return;
        }
    }

    // Create error message
    messageLength = TextCopyUntilCharacter(sEnglishText_Message_CheckFromPositionError,
                                           gDynamicMessageBuffer,
                                           CHAR_TERMINATOR);
    messageLength += TextCopyUntilCharacter(sLocationTextPointers[LANGUAGE_ENGLISH][gCurrentArea] + 1,
                                            gDynamicMessageBuffer + messageLength,
                                            CHAR_TERMINATOR);
    gDynamicMessageBuffer[messageLength++] = CHAR_EMPTY_SPACE;
    gDynamicMessageBuffer[messageLength++] = CHAR_OPENING_PARENTHESIS;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (itemX / 10) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + itemX % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_COMMA;
    gDynamicMessageBuffer[messageLength++] = CHAR_EMPTY_SPACE;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + (itemY / 10) % 10;
    gDynamicMessageBuffer[messageLength++] = CHAR_0 + itemY % 10;
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
    s32 isFirstTank;
    s32 messageID;
    u32 messageLength;
    u32 lineLength;
    u32 lineWidth;
    u16* pLine2;

    RandoCheckLocation(location);
    placement = &sPlacedItems[location];

    gPreventMovementTimer = SAMUS_ITEM_PMT;

    messageID = sItemMessages[placement->itemId];
    if (placement->playerName) {
        // Item name
        if (placement->itemName) {
            messageLength = 1;
            gDynamicMessageBuffer[messageLength++] = CHAR_COLOR_MASK | 5;
            messageLength += TextCopyUntilCharacter(placement->itemName,
                                                    gDynamicMessageBuffer + messageLength,
                                                    CHAR_TERMINATOR);
            lineWidth = TextGetStringWidth(gDynamicMessageBuffer + 2, messageLength - 2);  // Drop width and color
            gDynamicMessageBuffer[0] = CHAR_WIDTH_MASK | (224 - lineWidth) / 2;
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
        isFirstTank = FALSE;
        switch (placement->itemId) {
            case ITEM_ETANK:
                if (sStartingHealthAmmo.energy + sTankIncreaseAmount[gDifficulty].energy > 1299)
                    break;
                gEquipment.maxEnergy += sTankIncreaseAmount[gDifficulty].energy;
                gEquipment.currentEnergy = gEquipment.maxEnergy;
                messageID = MESSAGE_ENERGY_TANK_ACQUIRED;
                break;
            case ITEM_MISSILE:
            case ITEM_MISSILE_TANK:
                if (gEquipment.maxMissiles == 0)
                    isFirstTank = TRUE;
                gEquipment.maxMissiles += sTankIncreaseAmount[gDifficulty].missile;
                gEquipment.currentMissiles += sTankIncreaseAmount[gDifficulty].missile;
                messageID = isFirstTank ? MESSAGE_FIRST_MISSILE_TANK : MESSAGE_MISSILE_TANK_ACQUIRED;
                break;
            case ITEM_SUPER:
            case ITEM_SUPER_MISSILE_TANK:
                if (gEquipment.maxSuperMissiles == 0)
                    isFirstTank = TRUE;
                gEquipment.maxSuperMissiles += sTankIncreaseAmount[gDifficulty].superMissile;
                gEquipment.currentSuperMissiles += sTankIncreaseAmount[gDifficulty].superMissile;
                messageID = isFirstTank ? MESSAGE_FIRST_SUPER_MISSILE_TANK : MESSAGE_SUPER_MISSILE_TANK_ACQUIRED;
                break;
            case ITEM_POWER_BOMB:
            case ITEM_POWER_BOMB_TANK:
                if (gEquipment.maxPowerBombs == 0)
                    isFirstTank = TRUE;
                gEquipment.maxPowerBombs += sTankIncreaseAmount[gDifficulty].powerBomb;
                gEquipment.currentPowerBombs += sTankIncreaseAmount[gDifficulty].powerBomb;
                messageID = isFirstTank ? MESSAGE_FIRST_POWER_BOMB_TANK : MESSAGE_POWER_BOMB_TANK_ACQUIRED;
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
                if (!sRandoSeed.options.unknownItemsAlwaysUsable && gEquipment.suitType != SUIT_FULLY_POWERED)
                    messageID = MESSAGE_UKNOWN_ITEM_PLASMA;
                break;
            case ITEM_BOMB:
                gEquipment.beamBombs |= BBF_BOMBS;
                break;
            case ITEM_VARIA_SUIT:
                gEquipment.suitMisc |= SMF_VARIA_SUIT;
                break;
            case ITEM_GRAVITY_SUIT:
                gEquipment.suitMisc |= SMF_GRAVITY_SUIT;
                if (!sRandoSeed.options.unknownItemsAlwaysUsable && gEquipment.suitType != SUIT_FULLY_POWERED)
                    messageID = MESSAGE_UNKNOWN_ITEM_GRAVITY;
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
                if (!sRandoSeed.options.unknownItemsAlwaysUsable && gEquipment.suitType != SUIT_FULLY_POWERED)
                    messageID = MESSAGE_UNKNOWN_ITEM_SPACE_JUMP;
                break;
            case ITEM_POWER_GRIP:
                gEquipment.suitMisc |= SMF_POWER_GRIP;
                break;
        }
    }

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, messageID, 6, gSamusData.yPosition, gSamusData.xPosition, 0);
}
