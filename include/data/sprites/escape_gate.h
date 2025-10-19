#ifndef ESCAPE_GATE_DATA_H
#define ESCAPE_GATE_DATA_H

#include "types.h"
#include "oam.h"

extern const u8 sEscapeGateAndTimerGfx[2048];
extern const u16 sEscapeGateAndTimerPal[16];
extern const u16 sEscapeGateFlashingPal[96];

extern const struct FrameData sEscapeGateOam_Closed[2];
extern const struct FrameData sEscapeGateOam_Opening[18];
extern const struct FrameData sEscapeGateOam_Opened[2];

#endif /* ESCAPE_GATE_DATA_H */
