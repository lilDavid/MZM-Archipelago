#ifndef ELEVATOR_STATUE_DATA_H
#define ELEVATOR_STATUE_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sElevatorStatuesGfx[1122];
extern const u16 sElevatorStatuesPal[64];

extern const struct FrameData sKraidElevatorStatueOam_Idle[2];
extern const struct FrameData sKraidElevatorStatueOam_Falling[13];
extern const struct FrameData sElevatorStatueDebrisOam_Kraid[12];
extern const struct FrameData sKraidElevatorStatueOam_Fallen[2];

extern const struct FrameData sRidleyElevatorStatueOam_Idle[2];
extern const struct FrameData sRidleyElevatorStatueOam_Falling[13];
extern const struct FrameData sElevatorStatueDebrisOam_Ridley[12];
extern const struct FrameData sRidleyElevatorStatueOam_Fallen[2];

extern const struct FrameData sElevatorStatueDebrisOam_Dust[20];

#endif /* ELEVATOR_STATUE_DATA_H */
