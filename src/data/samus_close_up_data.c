#include "data/samus_close_up_data.h"
#include "macros.h"

const u16 sSamusCloseUpPal[6 * 16] = INCBIN_U16("data/close_up/palette.pal");
const u32 sSamusCloseUpGfx[2319] = INCBIN_U32("data/close_up/close_up.gfx.lz");

const u32 sSamusCloseUpEyesGfx_1[80] = INCBIN_U32("data/close_up/eyes_1.gfx");
const u32 sSamusCloseUpEyesGfx_2[80] = INCBIN_U32("data/close_up/eyes_2.gfx");
const u32 sSamusCloseUpEyesGfx_3[1376] = INCBIN_U32("data/close_up/eyes_3.gfx");

const u32 sSamusCloseUpBackgroundMap[385] = INCBIN_U32("data/close_up/background.tt");
const u32 sSamusCloseUpEyesTiletable[98] = INCBIN_U32("data/close_up/eyes.tt");
