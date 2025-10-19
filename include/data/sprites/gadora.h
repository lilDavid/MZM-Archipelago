#ifndef GADORA_DATA_H
#define GADORA_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sGadoraGfx[585];
extern const u16 sGadoraPal[32];

extern const struct FrameData sGadoraOam_EyeClosed[5];

extern const struct FrameData sGadoraOam_Warning[7];

extern const struct FrameData sGadoraOam_OpeningEye[7];

extern const struct FrameData sGadoraBeamOam_Moving[5];

extern const struct FrameData sGadoraOam_EyeMoving[7];

extern const struct FrameData sGadoraOam_ClosingEye[5];

extern const struct FrameData sGadoraOam_Death[5];

extern const struct FrameData sGadoraOam_EyeOpened[7];

extern const struct FrameData sGadoraOam_BeforeClosing[5];

#endif /* GADORA_DATA_H */
