#include "rando/game_start.h"

#include "types.h"
#include "event.h"
#include "in_game_cutscene.h"

#include "constants/event.h"
#include "constants/in_game_cutscene.h"


#define DEBUG_SKIP_BOSSES 0

void RandoSetStartingEvents(void) {
    s32 i;

    EventFunction(EVENT_ACTION_SETTING, EVENT_FULLY_POWERED_SUIT_OBTAINED);  // For less stupid Chozodia access
    for (i = EVENT_ENTER_NORFAIR_DEMO_PLAYED; i <= EVENT_STATUE_SCREW_ATTACK_GRABBED; i++)
        EventFunction(EVENT_ACTION_SETTING, i);
    EventFunction(EVENT_ACTION_CLEARING, EVENT_ENTER_RIDLEY_DEMO_PLAYED);

    InGameCutsceneCheckFlag(TRUE, IGC_LONG_BEAM_HINT);

#if DEBUG_SKIP_BOSSES
    EventFunction(EVENT_ACTION_SETTING, EVENT_KRAID_KILLED);
    EventFunction(EVENT_ACTION_SETTING, EVENT_RIDLEY_KILLED);
    EventFunction(EVENT_ACTION_SETTING, EVENT_KRAID_STATUE_OPENED);
    EventFunction(EVENT_ACTION_SETTING, EVENT_RIDLEY_STATUE_OPENED);
    for (i = EVENT_FIRST_METROID_ROOM_CLEARED; i <= EVENT_ZEBETITE_FOUR_DESTROYED; i++)
        EventFunction(EVENT_ACTION_SETTING, i);
#endif // DEBUG_SKIP_BOSSES
}
