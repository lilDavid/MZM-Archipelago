#ifndef MAP_STATION_DATA_H
#define MAP_STATION_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sMapStationGfx[680];
extern const u16 sMapStationPal[64];

extern const struct FrameData sMapStationOam_Idle[2];

extern const struct FrameData sMapStationOam_GrabbingSamus[10];

extern const struct FrameData sMapStationOam_Downloading[4];

extern const struct FrameData sMapStationOam_Retracting[2];

extern const struct FrameData sMapStationOam_Inactive[21];

extern const struct FrameData sMapStationPartOam_BackScreenIdle[5];

extern const struct FrameData sMapStationPartOam_BackScreenDownloading[5];

extern const struct FrameData sMapStationPartOam_BackScreenDownloaded[5];

extern const struct FrameData sMapStationPartOam_FrontScreenIdle[7];

extern const struct FrameData sMapStationPartOam_FrontScreenDownloading[7];

extern const struct FrameData sMapStationPartOam_FrontScreenDownloaded[6];

#endif /* MAP_STATION_DATA_H */
