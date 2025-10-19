#ifndef WORKER_ROBOT_DATA_H
#define WORKER_ROBOT_DATA_H

#include "types.h"
#include "macros.h"
#include "oam.h"

extern const u32 sWorkerRobotGfx[376];
extern const u16 sWorkerRobotPal[32];

extern const struct FrameData sWorkerRobotOam_Walking[9];
extern const struct FrameData sWorkerRobotOam_WalkingBackwards[9];
extern const struct FrameData sWorkerRobotOam_Standing[2];
extern const struct FrameData sWorkerRobotOam_BackToSleep[9];
extern const struct FrameData sWorkerRobotOam_Sleeping[2];
extern const struct FrameData sWorkerRobotOam_GoingToSleep[3];
extern const struct FrameData sWorkerRobotOam_TurningAround[3];
extern const struct FrameData sWorkerRobotOam_WakingUp[9];

#endif /* WORKER_ROBOT_DATA_H */
