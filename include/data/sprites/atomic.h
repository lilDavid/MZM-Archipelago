#ifndef ATOMIC_DATA_H
#define ATOMIC_DATA_H

#include "types.h"
#include "oam.h"

extern const s16 sAtomicIdleYMovement[65];

extern const s16 sAtomicIdleXMovement[81];

extern const u32 sAtomicGfx[752];
extern const u16 sAtomicPal[64];

extern const struct FrameData sAtomicOam_Idle[13];

extern const struct FrameData sAtomicElectricityOam_MovingVertical[13];
extern const struct FrameData sAtomicElectricityOam_MovingVertical_Unused[5];
extern const struct FrameData sAtomicElectricityOam_MovingDiagonal[13];
extern const struct FrameData sAtomicElectricityOam_MovingDiagonal_Unused[5];
extern const struct FrameData sAtomicElectricityOam_MovingHorizontal[13];
extern const struct FrameData sAtomicElectricityOam_MovingHorizontal_Unused[5];
extern const struct FrameData sAtomicElectricityOam_ExplodingNonDiagonal[8];
extern const struct FrameData sAtomicElectricityOam_ExplodingDiagonal[8];
extern const struct FrameData sAtomicElectricityOam_Charging[12];

#endif /* ATOMIC_DATA_H */
