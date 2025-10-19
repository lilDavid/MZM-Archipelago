#ifndef DISPLAY_STRUCT_H
#define DISPLAY_STRUCT_H

#include "types.h"

struct IoRegistersBackup {
    u16 Dispcnt_NonGameplay;
    u16 Bldcnt_NonGameplay;
    u8 BLDALPHA_NonGameplay_EVA;
    u8 BLDALPHA_NonGameplay_EVB;
    u8 BLDY_NonGameplay;
    u8 WININ_H;
    u8 WINOUT_L;
    u16 BG0CNT;
    u16 BG1CNT;
    u16 BG2CNT;
    u16 BG3CNT;
    u16 unk_12; // Used alongside BG0CNT
};

extern u16 gWrittenToWin1H;
extern u16 gWrittenToWin1V;
extern u16 gWrittenToBldcnt;
extern u16 gWrittenToBldcnt_Internal;

extern u16 gBackdropColor;

extern u16 gWrittenToBldalpha;
extern u16 gWrittenToBldalpha_L;
extern u16 gWrittenToBldalpha_H;
extern s8 gWrittenToBldy;
extern u16 gWrittenToBldy_NonGameplay;

extern u16 gWrittenToMosaic_H;
extern u16 gWrittenToMosaic_L;

extern u16 gDispcntBackup;
extern u16 gWrittenToDispcnt;
extern u8 gWrittenToWinIn_H;
extern u8 gWrittenToWinOut_L;
extern struct IoRegistersBackup gIoRegistersBackup;

#endif /* DISPLAY_STRUCT_H */
