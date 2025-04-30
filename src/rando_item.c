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

void RandoActivateItem(const struct RandoItem* item) {
    switch (item->itemType) {
        case RANDO_ITEM_BEAM_BOMBS:
            gEquipment.beamBombsActivation |= item->value;
            if (!UNKNOWN_ITEMS_ARE_USABLE)
                gEquipment.beamBombsActivation &= ~BBF_PLASMA_BEAM;
            if (!(gEquipment.suitMiscActivation & SMF_MORPH_BALL))
                gEquipment.beamBombsActivation &= ~BBF_BOMBS;
            if (item->value & (BBF_LONG_BEAM | BBF_ICE_BEAM | BBF_WAVE_BEAM | BBF_PLASMA_BEAM))
                ProjectileCallLoadGraphicsAndClearProjectiles();
            break;
        case RANDO_ITEM_SUIT_MISC:
            gEquipment.suitMiscActivation |= item->value;
            if (!UNKNOWN_ITEMS_ARE_USABLE)
                gEquipment.suitMiscActivation &= ~(SMF_GRAVITY_SUIT | SMF_SPACE_JUMP);
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

static u32 RandoCanMultiworld() {
    return gGameModeSub1 == SUB_GAME_MODE_PLAYING && !(gDisablePause || gPauseScreenFlag || gShipLandingFlag);
}

static u32 RandoCanDisplayMessage() {
    int i, j;
    u32 dangerousSpriteset;

    if (gIncomingMessage.data == NULL || gPreventMovementTimer)
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

static void RandoGiveMultiworldItem(u32 activate) {
    RandoGiveItem(&gIncomingItem);
    if (activate)
        RandoActivateItem(&gIncomingItem);
    gIncomingItem = sEmptyIncomingItem;
    gMultiworldItemCount += 1;
}

static void RandoAcceptMessage() {
    if (!RandoCanDisplayMessage())
        return;

    gPreventMovementTimer = SAMUS_ITEM_PMT;
    gCurrentRandoMessage = gIncomingMessage;
    gReceivingFromMultiworld = TRUE;

    // (Hopefully) fix the bug where the item acquisition freezes Samus in place instead of showing the message
    if (SpriteSpawnPrimary(PSPRITE_ITEM_BANNER, MESSAGE_DUMMY, 6, gSamusData.yPosition, gSamusData.xPosition, 0) == UCHAR_MAX) {
        gPreventMovementTimer = 0;
        gReceivingFromMultiworld = FALSE;
        return;
    }

    if (gIncomingItem.itemType != RANDO_ITEM_NONE) {
        RandoGiveMultiworldItem(FALSE);
    }
}

void RandoHandleMultiworld() {
    if (!RandoCanMultiworld())
        return;

    RandoAcceptMessage();
    if (gIncomingItem.itemType != RANDO_ITEM_NONE && !gIncomingItem.waitForMessage) {
        RandoGiveMultiworldItem(gEquipment.suitType != SUIT_SUITLESS);
    }
}
