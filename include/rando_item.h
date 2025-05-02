#ifndef RANDO_ITEM_H
#define RANDO_ITEM_H

#include "types.h"
#include "event.h"

#include "constants/rando.h"
#include "constants/event.h"

#include "structs/rando.h"
#include "structs/room.h"


void RandoGiveItemFromCheck(u32 location);
u32 RandoIsLocationChecked(u32 location);

void RandoActivateAcquiredItem(void);

void RandoPlaceItemInSpriteGraphics(u32 location, u32 row, u32 column, u32 palette, u32 frames);

#endif  // RANDO_ITEM_H