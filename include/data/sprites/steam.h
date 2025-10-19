#ifndef STEAM_DATA_H
#define STEAM_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sSteamGfx[195];
extern const u16 sSteamPal[16];

extern const struct FrameData sSteamOam_HorizontalLarge[12];
extern const struct FrameData sSteamOam_VerticalLarge[12];
extern const struct FrameData sSteamOam_HorizontalSmall[10];
extern const struct FrameData sSteamOam_VerticalSmall[10];
extern const struct FrameData sSteamDiagonalOam_Large[12];
extern const struct FrameData sSteamDiagonalOam_Small[10];

#endif /* STEAM_DATA_H */
