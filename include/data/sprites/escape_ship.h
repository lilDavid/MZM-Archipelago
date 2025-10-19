#ifndef ESCAPE_SHIP_DATA_H
#define ESCAPE_SHIP_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sEscapeShipHoveringYMovement[65];

extern const s16 sEscapeShipHoveringXMovement[57];

extern const u32 sEscapeShipGfx[919];
extern const u16 sEscapeShipPal[64];
extern const u16 sEscapeShipFlashingPal[3 * 16];

extern const struct FrameData sEscapeShipOam_Idle[2];
extern const struct FrameData sEscapeShipOam_Opening[9];
extern const struct FrameData sEscapeShipOam_Closing[9];
extern const struct FrameData sEscapeShipOam_Flying[5];

extern const struct FrameData sEscapeShipPartOam_Top[5];
extern const struct FrameData sEscapeShipPartOam_Flames[4];
extern const struct FrameData sEscapeShipPartOam_Tail[2];
extern const struct FrameData sEscapeShipPartOam_TailMoving[26];

#endif /* ESCAPE_SHIP_DATA_H */
