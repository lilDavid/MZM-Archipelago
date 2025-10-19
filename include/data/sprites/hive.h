#ifndef HIVE_DATA_H
#define HIVE_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sMellowIdleYVelocity[65];

extern const s16 sMellowIdleXVelocity[81];

extern const u32 sHiveGfx[1799];
extern const u16 sHivePal[96];

extern const struct FrameData sMellowOam_Idle[6];
extern const struct FrameData sMellowOam_SamusDetected[6];

extern const struct FrameData sHiveOam_Idle[19];
extern const struct FrameData sHiveRootsOam_Idle[4];
extern const struct FrameData sHiveOam_Phase2[12];
extern const struct FrameData sHiveOam_Phase3[13];
extern const struct FrameData sHiveOam_Dying[32];

#endif /* HIVE_DATA_H */
