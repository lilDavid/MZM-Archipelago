#ifndef RANDO_ITEM_H
#define RANDO_ITEM_H

#include "types.h"

#include "constants/rando.h"

#include "structs/room.h"

void RandoGiveItemFromCheck(u32 location);
void RandoGiveItemFromPosition(u32 area, u32 room, u32 xPosition, u32 yPosition);
u32 RandoGetItemAtPosition(u32 area, u32 room, u32 xPosition, u32 yPosition);
u32 RandoIsLocationChecked(u32 location);

#endif  // RANDO_ITEM_H