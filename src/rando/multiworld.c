#include "rando/multiworld.h"

#include "types.h"
#include "macros.h"

#include "constants/escape.h"
#include "constants/game_state.h"
#include "constants/samus.h"
#include "constants/sprite.h"

#include "structs/connection.h"
#include "structs/escape.h"
#include "structs/game_state.h"
#include "structs/rando.h"
#include "structs/room.h"
#include "structs/samus.h"
#include "structs/sprite.h"

#include "data/rando_data.h"


static u32 RandoCanMultiworld() {
    return gSubGameMode1 == SUB_GAME_MODE_PLAYING && !(gDisablePause || gPauseScreenFlag || gShipLandingFlag);
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
        if (gSpritesetSpritesID[i] == PSPRITE_MESSAGE_BANNER)
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
    gCollectingLocation = RC_MULTIWORLD;

    // (Hopefully) fix the bug where the item acquisition freezes Samus in place instead of showing the message
    if (SpriteSpawnPrimary(PSPRITE_MESSAGE_BANNER, MESSAGE_DUMMY, 6, gSamusData.yPosition, gSamusData.xPosition, 0) == UCHAR_MAX) {
        gPreventMovementTimer = 0;
        gCollectingLocation = RC_NONE;
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
