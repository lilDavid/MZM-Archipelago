#ifndef SECURITY_GATE_DATA_H
#define SECURITY_GATE_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sSecurityGateGfx[122];
extern const u16 sSecurityGatePal[16];

extern const struct FrameData sSecurityGateOam_Opened[2];
extern const struct FrameData sSecurityGateOam_Closing[18];
extern const struct FrameData sSecurityGateOam_Closed[4];
extern const struct FrameData sSecurityGateOam_Opening[18];

#endif /* SECURITY_GATE_DATA_H */
