#include "rando/warp_to_start.h"

#include "audio_wrappers.h"
#include "save_file.h"

#include "constants/color_fading.h"
#include "constants/event.h"
#include "constants/samus.h"

#include "structs/audio.h"
#include "structs/color_effects.h"
#include "structs/samus.h"
#include "structs/rando.h"
#include "structs/room.h"

#include "data/engine_pointers.h"
#include "data/rando_data.h"


static void WarpToStartSetSamusLocation(void) {
    // If in stealth, give power suit back and un-kill Mother Brain
    if (gEquipment.suitType == SUIT_SUITLESS) {
        EventFunction(EVENT_ACTION_CLEARING, EVENT_MOTHER_BRAIN_KILLED);
        EventFunction(EVENT_ACTION_CLEARING, EVENT_ESCAPED_ZEBES);
        EventFunction(EVENT_ACTION_SETTING, EVENT_FULLY_POWERED_SUIT_OBTAINED);
        if (gRandoEquipment.customItems & CIF_FULLY_POWERED_SUIT) {
            gEquipment.beamBombsActivation = gEquipment.beamBombs;
            gEquipment.suitMiscActivation = gEquipment.suitMisc;
            gEquipment.suitType = !!(gEquipment.suitMisc & SMF_ALL_SUITS);
        } else {
            gEquipment.beamBombsActivation = gEquipment.beamBombs & ~BBF_PLASMA_BEAM;
            gEquipment.suitMiscActivation = gEquipment.suitMisc & ~SMF_UNKNOWN_ITEMS;
            gEquipment.suitType = SUIT_NORMAL;
        }
    }

    gSamusData.xPosition = gPreviousXPosition = sStartingLocation.samus.xPosition;
    gSamusData.yPosition = gPreviousYPosition = sStartingLocation.samus.yPosition;
    gSamusData.timer = 0;
    gSamusData.standingStatus = STANDING_GROUND;
    gPreventMovementTimer = CONVERT_SECONDS(6);

    gCurrentArea = gAreaBeforeTransition = sStartingLocation.area;
    gCurrentRoom = sStartingLocation.room;
    gLastDoorUsed = sStartingLocation.lastDoorUsed;
    gUseMotherShipDoors = sStartingLocation.useMotherShipDoors;
    gMusicInfo.musicTrack = sAreaRoomEntryPointers[gCurrentArea][gCurrentRoom].musicTrack;

    gCamera = sStartingLocation.camera;
    gBg1XPosition = gCamera.xPosition;
    gBg1YPosition = gCamera.yPosition;
    ScrollBg3Related();
    ScrollProcessGeneral();
}

void RandoWarpToStart(void) {
    StopAllMusicsAndSounds();
    ResetMusicVolume();

    unk_75c04(FALSE);  // Reload last save
    if (!gHasSaved)
        return;  // Play intro as if you had died or reset

    WarpToStartSetSamusLocation();
    gColorFading.type = COLOR_FADING_NO_TRANSITION;
}
