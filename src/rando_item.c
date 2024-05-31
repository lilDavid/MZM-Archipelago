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
}

void RandoGiveItemFromCheck(u32 location) {
    const struct PlacedItem* placement;
    s32 isFirstTank;
    s32 messageID;
    u16* pMessage;
    u16* pLine2;
    const u16* pName;
    u32 textWidth;

    RandoCheckLocation(location);
    placement = &sPlacedItems[location];

    gPreventMovementTimer = SAMUS_ITEM_PMT;

    messageID = sItemMessages[placement->itemId];
    if (placement->playerName) {
        pMessage = gDynamicMessageBuffer;
        if (placement->itemName) {
            textWidth = 0;
            pName = placement->itemName;

            pMessage++;
            *pMessage = CHAR_COLOR_MASK | 5;
            pMessage++;
            while (*pName != 0 && pName - placement->itemName < 32) {
                textWidth += TextGetCharacterWidth(*pName);
                *pMessage = *pName;
                pMessage++;
                pName++;
            }
            *gDynamicMessageBuffer = CHAR_WIDTH_MASK | (224 - textWidth) / 2;
        } else {
            pName = sMessageTextPointers[gLanguage][messageID];
            while (*pName != CHAR_NEW_LINE) {
                *pMessage = *pName;
                pMessage++;
                pName++;
            }
        }
        *pMessage = CHAR_NEW_LINE;
        pMessage++;

        pLine2 = pMessage;
        pMessage++;
        textWidth = 0;

        pName = sEnglishText_MessageFragment_Sent;
        while (*pName != CHAR_TERMINATOR) {
            textWidth += TextGetCharacterWidth(*pName);
            *pMessage = *pName;
            pMessage++;
            pName++;
        }
        pName = placement->playerName;
        while (*pName != 0) {
            textWidth += TextGetCharacterWidth(*pName);
            *pMessage = *pName;
            pMessage++;
            pName++;
        }
        textWidth += TextGetCharacterWidth(CHAR_DOT);
        *pMessage = CHAR_DOT;
        pMessage++;

        *pLine2 = CHAR_WIDTH_MASK | (224 - textWidth) / 2;
        *pMessage = CHAR_TERMINATOR;

        messageID = MESSAGE_DYNAMIC;
    } else {
        isFirstTank = FALSE;
        switch (placement->itemId) {
            case ITEM_ETANK:
                if (sNumberOfTanksPerArea[MAX_AMOUNT_OF_AREAS - 1].energy * sTankIncreaseAmount[gDifficulty].energy + sStartingHealthAmmo.energy < gEquipment.maxMissiles + sTankIncreaseAmount[gDifficulty].energy)
                    break;
                gEquipment.maxEnergy += sTankIncreaseAmount[gDifficulty].energy;
                gEquipment.currentEnergy = gEquipment.maxEnergy;
                messageID = MESSAGE_ENERGY_TANK_ACQUIRED;
                break;
            case ITEM_MISSILE:
            case ITEM_MISSILE_TANK:
                if (sNumberOfTanksPerArea[MAX_AMOUNT_OF_AREAS - 1].missile * sTankIncreaseAmount[gDifficulty].missile + sStartingHealthAmmo.missile < gEquipment.maxMissiles + sTankIncreaseAmount[gDifficulty].missile)
                    break;
                if (gEquipment.maxMissiles == 0)
                    isFirstTank = TRUE;
                gEquipment.maxMissiles += sTankIncreaseAmount[gDifficulty].missile;
                gEquipment.currentMissiles += sTankIncreaseAmount[gDifficulty].missile;
                messageID = isFirstTank ? MESSAGE_FIRST_MISSILE_TANK : MESSAGE_MISSILE_TANK_ACQUIRED;
                break;
            case ITEM_SUPER:
            case ITEM_SUPER_MISSILE_TANK:
                if (sNumberOfTanksPerArea[MAX_AMOUNT_OF_AREAS - 1].superMissile * sTankIncreaseAmount[gDifficulty].superMissile + sStartingHealthAmmo.superMissile < gEquipment.maxMissiles + sTankIncreaseAmount[gDifficulty].superMissile)
                    break;
                if (gEquipment.maxSuperMissiles == 0)
                    isFirstTank = TRUE;
                gEquipment.maxSuperMissiles += sTankIncreaseAmount[gDifficulty].superMissile;
                gEquipment.currentSuperMissiles += sTankIncreaseAmount[gDifficulty].superMissile;
                messageID = isFirstTank ? MESSAGE_FIRST_SUPER_MISSILE_TANK : MESSAGE_SUPER_MISSILE_TANK_ACQUIRED;
                break;
            case ITEM_POWER_BOMB:
            case ITEM_POWER_BOMB_TANK:
                if (sNumberOfTanksPerArea[MAX_AMOUNT_OF_AREAS - 1].powerBomb * sTankIncreaseAmount[gDifficulty].powerBomb + sStartingHealthAmmo.powerBomb < gEquipment.maxMissiles + sTankIncreaseAmount[gDifficulty].powerBomb)
                    break;
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

    SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, messageID, 6, gSamusData.yPosition, gSamusData.xPosition, 0);
}
