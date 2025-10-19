#include "rando/status_screen.h"

#include "types.h"

#include "structs/menus/pause_screen.h"
#include "structs/rando.h"
#include "structs/samus.h"

#include "data/menus/pause_screen_data.h"
#include "data/rando_data.h"
#include "data/shortcut_pointers.h"


void RandoDrawStatusScreenDNA() {
    s32 i;
    s32 j;
    u32 position;
    u16* dst;

    dst = VRAM_BASE + 0xC000;
    for (i = 0; i < ARRAY_SIZE(sRandoStatusScreenData); i++) {
        position = sRandoStatusScreenData[i][RANDO_ABILITY_GROUP_Y] * HALF_BLOCK_SIZE +
            sRandoStatusScreenData[i][RANDO_ABILITY_GROUP_X_LEFT];

        for (j = 0; j <= sRandoStatusScreenData[i][RANDO_ABILITY_GROUP_X_RIGHT]; j++, position++) {
            dst[position] = PAUSE_SCREEN_EWRAM.statusScreenTilemap[position];
        }
    }
}


void RandoDrawSingleDNAAmount(u8 group, u8 amount, u8 palette, u8 isMax) {
    u16 baseTile;
    u16* pTilemap;
    u32 position;
    s32 size;
    s32 value;
    s32 i;
    u32 var_0;
    s32 digits;

    // if (group == RANDO_ABILITY_GROUP_CURRENT_DNA || group == RANDO_ABILITY_GROUP_REQUIRED_DNA)
        baseTile = 0xB2E0;
    // else
    //     baseTile = 0xB08C;

    pTilemap = PAUSE_SCREEN_EWRAM.statusScreenTilemap;
    position = sRandoStatusScreenData[group][RANDO_ABILITY_GROUP_Y] * HALF_BLOCK_SIZE + sRandoStatusScreenData[group][RANDO_ABILITY_GROUP_X_LEFT];
    pTilemap = &pTilemap[position];
    digits = sRandoStatusScreenData[group][RANDO_ABILITY_GROUP_X_RIGHT] - sRandoStatusScreenData[group][RANDO_ABILITY_GROUP_X_LEFT];
    value = sPowersOfTen[digits];
    digits++;

    var_0 = FALSE;
    i = 0;

    for (; value > 0; value /= 10, i++)
    {
        size = amount / value % 10;
        if (size == 0)
        {
            size = 128;
            if (value != 1 && !var_0)
            {
                if (!isMax)
                    size = baseTile & 0xFFF;
                else
                {
                    i--;
                    continue;
                }
            }
        }
        else
        {
            var_0 = TRUE;
            size += 128;
        }

        if (size != 0)
        {
            pTilemap[i] = palette << 0xC | size;
        }
        else
        {
            i--;
        }

    }

    while (digits != i)
    {
        pTilemap[i] = (baseTile & 0xFFF) | palette << 0xC;
        i++;
    }
}

void RandoDrawDNACount() {
    RandoDrawSingleDNAAmount(RANDO_ABILITY_GROUP_CURRENT_DNA, gRandoEquipment.metroidDNA, 11, FALSE);
    RandoDrawSingleDNAAmount(RANDO_ABILITY_GROUP_REQUIRED_DNA, sRandoSeed.options.metroidDnaRequired, 11, TRUE);
}
