#ifndef ROOM_MUSIC_H
#define ROOM_MUSIC_H

#include "types.h"

#include "constants/connection.h"

void CheckPlayRoomMusicTrack(Area area, u8 room);
void CheckPlayLoadingJingle(void);
void UpdateMusicWhenPausing(void);
void UpdateMusicAfterPause(void);

#endif /* ROOM_MUSIC_H */
