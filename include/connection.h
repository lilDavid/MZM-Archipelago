#ifndef CONNECTION_H
#define CONNECTION_H

#include "types.h"

#include "constants/connection.h"

// Functions

void ConnectionUpdateHatches(void);
void ConnectionUpdateHatchAnimation(boolu8 dontSetRaw, u32 hatch);
void ConnectionHatchFlashingAnimation(u8 hatch);
void ConnectionOverrideOpenedHatch(u8 hatch, u32 type);
boolu32 ConnectionCheckEnterDoor(u16 yPosition, u16 xPosition);
boolu32 ConnectionCheckAreaConnection(u16 yPosition, u16 xPosition);
void ConnectionProcessDoorType(DoorType type);
u8 ConnectionFindEventBasedDoor(u8 sourceDoor);
boolu32 ConnectionSetHatchAsOpened(HatchAction action, u8 hatch);
void ConnectionCheckUnlockDoors(void);
void ConnectionHatchStartLockAnimation(boolu8 dontSetRaw, u8 hatch, u8 status);
void ConnectionLockHatches(boolu8 isEvent);
void ConnectionLoadDoors(void);
void ConnectionLockHatchesWithTimer(void);
void ConnectionCheckHatchLockEvents(void);
void ConnectionCheckPlayCutsceneDuringTransition(Area area, u8 dstRoomPlusOne);
void ConnectionCheckPlayCutsceneDuringAreaConnection(void);

#endif /* CONNECTION_H */