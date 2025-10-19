#ifndef MINIMAP_H
#define MINIMAP_H

#include "types.h"

#include "constants/connection.h"
#include "constants/event.h"

#ifdef DEBUG
void MinimapDrawRoomInfo(void);
#endif // DEBUG

void MinimapUpdate(void);
void MinimapCheckOnTransition(void);
void MinimapDraw(void);
void MinimapSetTilesWithObtainedItems(Area area, u16* dst);
void MinimapSetDownloadedTiles(Area area, u16* dst);
void MinimapUpdateForCollectedItem(u8 xPosition, u8 yPosition);
u32 MinimapCheckIsTileExplored(u8 xPosition, u8 yPosition);
void MinimapLoadTilesWithObtainedItems(void);
void MinimapUpdateChunk(Event event);

#endif /* MINIMAP_H */