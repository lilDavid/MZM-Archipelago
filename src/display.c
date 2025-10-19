#include "display.h"
#include "gba.h"

#include "structs/display.h"
#include "structs/color_effects.h"

/**
 * @brief 57a24 | d4 | Writes to the IO registers using the WrittenToXXX globals
 * 
 */
void IoWriteRegisters(void)
{
    if (gWrittenToDispcnt)
    {
        WRITE_16(REG_DISPCNT, gWrittenToDispcnt);
        gWrittenToDispcnt = 0;
    }

    if (gWrittenToBldalpha)
    {
        WRITE_16(REG_BLDALPHA, gWrittenToBldalpha);
        gWrittenToBldalpha = 0;
    }

    if (gWrittenToBldy >= 0)
    {
        WRITE_16(REG_BLDY, gWrittenToBldy);
        gWrittenToBldy = -1;
    }

    if (gWrittenToWinIn_H)
    {
        WRITE_8(REG_WININ + 1, gWrittenToWinIn_H);
        gWrittenToWinIn_H = 0;
    }

    if (gWrittenToWinOut_L)
    {
        WRITE_8(REG_WINOUT, gWrittenToWinOut_L);
        gWrittenToWinOut_L = 0;
    }

    if (gWrittenToWin1H | gWrittenToWin1V)
    {
        WRITE_16(REG_WIN1H, gWrittenToWin1H);
        WRITE_16(REG_WIN1V, gWrittenToWin1V);
        gWrittenToWin1H = 0;
        gWrittenToWin1V = 0;
    }

    if (gWrittenToBldcnt)
    {
        WRITE_16(REG_BLDCNT, gWrittenToBldcnt);
        gWrittenToBldcnt = 0;
    }

    CheckTransferFadedPalette();
    AnimatedGraphicsTransfer();
}

/**
 * @brief 57af8 | e0 | Writes to the IO registers using the WrittenToXXX globals during a transition
 * 
 */
void IoWriteRegistersDuringTransition(void)
{
    if (gWrittenToDispcnt)
    {
        WRITE_16(REG_DISPCNT, gWrittenToDispcnt);
        gWrittenToDispcnt = 0;
    }

    if (gWrittenToBldalpha)
    {
        WRITE_16(REG_BLDALPHA, gWrittenToBldalpha);
        gWrittenToBldalpha = 0;
    }

    if (gWrittenToWinIn_H)
    {
        WRITE_8(REG_WININ + 1, gWrittenToWinIn_H);
        gWrittenToWinIn_H = 0;
    }

    if (gWrittenToWinOut_L)
    {
        WRITE_8(REG_WINOUT, gWrittenToWinOut_L);
        gWrittenToWinOut_L = 0;
    }

    if (gWrittenToWin1H | gWrittenToWin1V)
    {
        WRITE_16(REG_WIN1H, gWrittenToWin1H);
        WRITE_16(REG_WIN1V, gWrittenToWin1V);
        gWrittenToWin1H = 0;
        gWrittenToWin1V = 0;
    }

    if (gWrittenToBldcnt)
    {
        WRITE_16(REG_BLDCNT, gWrittenToBldcnt);
        gWrittenToBldcnt = 0;
    }

    if (gBg1CntDuringDoorTransition)
    {
        WRITE_16(REG_BG1CNT, gBg1CntDuringDoorTransition);
        gBg1CntDuringDoorTransition = 0;
    }

    if (gBg3CntDuringDoorTransition)
    {
        WRITE_16(REG_BG3CNT, gBg3CntDuringDoorTransition);
        gBg3CntDuringDoorTransition = 0;
    }

    CheckTransferFadedPalette();
    AnimatedGraphicsTransfer();
}

/**
 * 57bd8 | 74 | Updates the DISPCNT (Display Control) register
 * 
 * @param operation Operation (0 = Remove, 1 = Add)
 * @param value Value to apply
 */
void IoUpdateDispcnt(u8 operation, u16 value)
{
    if (value != 0)
    {
        gWrittenToDispcnt = READ_16(REG_BASE);
        if (operation)
            gDispcntBackup = gIoRegistersBackup.Dispcnt_NonGameplay | value;
        else
            gDispcntBackup = gIoRegistersBackup.Dispcnt_NonGameplay & ~value;

        if (gDispcntBackup != gIoRegistersBackup.Dispcnt_NonGameplay)
        {
            if (gWrittenToDispcnt == gIoRegistersBackup.Dispcnt_NonGameplay)
                gWrittenToDispcnt = gDispcntBackup;
            else
                gWrittenToDispcnt = 0;

            gIoRegistersBackup.Dispcnt_NonGameplay = gDispcntBackup;
            gDispcntBackup = value;
        }
    }
}
