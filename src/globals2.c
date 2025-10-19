#include "structs/animated_graphics.h"
#include "structs/audio.h"
#include "structs/bg_clip.h"
#include "structs/block.h"
#include "structs/cable_link.h"
#include "structs/chozodia_escape.h"
#include "structs/clipdata.h"
#include "structs/color_effects.h"
#include "structs/connection.h"
#include "structs/cutscene.h"
#include "structs/demo.h"
#include "structs/display.h"
#include "structs/ending_and_gallery.h"
#include "structs/escape.h"
#include "structs/fusion_gallery.h"
#include "structs/game_state.h"
#include "structs/haze.h"
#include "structs/hud.h"
#include "structs/intro.h"
#include "structs/in_game_cutscene.h"
#include "structs/in_game_timer.h"
#include "structs/link.h"
#include "structs/menu.h"
#include "structs/minimap.h"
#include "structs/multiboot.h"
#include "structs/particle.h"
#include "structs/power_bomb_explosion.h"
#include "structs/projectile.h"
#include "structs/room.h"
#include "structs/samus.h"
#include "structs/save_file.h"
#include "structs/screen_shake.h"
#include "structs/scroll.h"
#include "structs/sprite.h"
#include "structs/text.h"
#include "structs/time_attack.h"
#include "structs/tourian_escape.h"
#include "structs/transfer.h"
#include "structs/transparency.h"
#include "structs/visual_effects.h"

#include "sprite_debris.h"
#include "oam.h"
#include "temp_globals.h"

#ifdef RAM_PADDING
IWRAM_DATA u8 gUnk_3005908[8] = {};
#endif

IWRAM_DATA struct TrackData gTrackData8 = {};
IWRAM_DATA struct TrackData gTrackData3 = {};
IWRAM_DATA struct TrackData gTrackData1 = {};
IWRAM_DATA struct TrackData gTrackData6 = {};
IWRAM_DATA struct TrackData gTrackData4 = {};
IWRAM_DATA struct TrackData gTrackData0 = {};
IWRAM_DATA struct TrackData gTrackData7 = {};
IWRAM_DATA struct TrackData gTrackData2 = {};
IWRAM_DATA struct TrackData gTrackData5 = {};
IWRAM_DATA u8 gLastSendQueueCount = 0;

#ifdef RAM_PADDING
IWRAM_DATA u8 gUnk_3005B51[3] = {};
#endif

IWRAM_DATA u8 gLastRecvQueueCount = 0;

#ifdef RAM_PADDING
IWRAM_DATA u8 gUnk_3005B55[11] = {};
#endif

IWRAM_DATA struct LinkInfo gLink = {};
