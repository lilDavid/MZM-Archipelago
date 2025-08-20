#include "rando/graphics.h"

#include "gba.h"
#include "types.h"

#include "constants/animated_graphics.h"
#include "constants/clipdata.h"
#include "constants/rando.h"

#include "structs/animated_graphics.h"
#include "structs/clipdata.h"
#include "structs/rando.h"
#include "structs/room.h"

#include "data/rando_data.h"


void RandoLoadItemTiles(void) {
    u32 i, j;
    u32 itemRoom;

    for (itemRoom = 0;
         itemRoom < sRandoAreaItemListLengths[gCurrentArea] && sRandoAreaItemLists[gCurrentArea][itemRoom] != gCurrentRoom;
         itemRoom += 2);
    for (i = 0;
         itemRoom < sRandoAreaItemListLengths[gCurrentArea] && sRandoAreaItemLists[gCurrentArea][itemRoom] == gCurrentRoom;
         i++, itemRoom += 2)
    {
        const struct PlacedItem* placement;
        u32 baseTile, palette;

        placement = &sPlacedItems[sRandoAreaItemLists[gCurrentArea][itemRoom + 1]];
        if (sRandoItemToTankTilemap[placement->item.itemType] != 0) {
            palette = UCHAR_MAX;
            baseTile = sRandoItemToTankTilemap[placement->item.itemType];
        } else {
            palette = sRandoPaletteSlots[gCurrentRoomEntry.tileset * 2 + i];
            baseTile = 4 * (sRandoAnimatedTileGaps[gAnimatedGraphicsEntry.tileset] + i) | ((palette == UCHAR_MAX ? 0 : palette) << 12);
        }
        for (j = 0; j < 4; j++) {
            gCommonTilemap[4 * (CLIPDATA_TILEMAP_ENERGY_TANK + i) + j] = baseTile + j;
            gTilemap[4 * (0x48 + (i ^ 1)) + j] = baseTile + j;
        }

        if (palette != UCHAR_MAX)
            DmaTransfer(3, placement->sprite->pal, PALRAM_BASE + (palette * sizeof(u16[16])), sizeof(u16[16]), 16);
    }
    for (; i < 4; i++) {
        // Set the rest to the placeholder gem
        u32 baseTile = 4 * (sRandoAnimatedTileGaps[gAnimatedGraphicsEntry.tileset] + i);
        for (j = 0; j < 4; j++) {
            gCommonTilemap[4 * (CLIPDATA_TILEMAP_ENERGY_TANK + i) + j] = baseTile + j;
            gTilemap[4 * (0x48 + (i ^ 1)) + j] = baseTile + j;
        }
    }
}

void RandoLoadAnimatedGraphics(void) {
    s32 i;
    s32 itemRoom;
    const u8* src;
    const u8* dst;
    struct AnimatedGraphicsInfo* pGraphics;

    // Rando items
    for (itemRoom = 0; sRandoAreaItemLists[gCurrentArea][itemRoom] != gCurrentRoom; itemRoom += 2)
        if (itemRoom >= sRandoAreaItemListLengths[gCurrentArea])
            return;
    for (i = 0, pGraphics = gAnimatedGraphicsData + sRandoAnimatedTileGaps[gAnimatedGraphicsEntry.tileset];
         i < 2;
         i++, pGraphics++, itemRoom += 2)
    {
        if (itemRoom >= sRandoAreaItemListLengths[gCurrentArea] || sRandoAreaItemLists[gCurrentArea][itemRoom] != gCurrentRoom)
            return;
        if (sPlacedItems[sRandoAreaItemLists[gCurrentArea][itemRoom + 1]].item.itemType <= RANDO_ITEM_POWER_BOMBS)
            continue;

        pGraphics->type = ANIMATED_GFX_TYPE_NORMAL;
        pGraphics->framesPerState = 10;
        pGraphics->numberOfStates = 4;

        pGraphics->animationDurationCounter = 0;
        pGraphics->currentAnimationFrame = 0;
        pGraphics->pGraphics = sPlacedItems[sRandoAreaItemLists[gCurrentArea][itemRoom + 1]].sprite->gfx;

        src = pGraphics->pGraphics;
        dst = ANIMATED_GFX_VRAM_POS(i + sRandoAnimatedTileGaps[gAnimatedGraphicsEntry.tileset]);
        DMA_SET(3, src, dst, DMA_ENABLE << 16 | ANIMATED_GFX_SIZE_16_BITS);
    }
}

void RandoRevealHiddenBlocks(void) {
    s32 i, j;
    s32 position, clipBehavior, block, appearance;

    for (i = 0; i < gBgPointersAndDimensions.clipdataHeight; i++)
    {
        for (j = 0; j < gBgPointersAndDimensions.clipdataWidth; j++)
        {
            position = i * gBgPointersAndDimensions.clipdataWidth + j;

            clipBehavior = gTilemapAndClipPointers.pClipBehaviors[gBgPointersAndDimensions.pClipDecomp[position]];
            if (clipBehavior == CLIP_BEHAVIOR_NONE)
                continue;
            block = BEHAVIOR_TO_BLOCK(clipBehavior);
            if (block < 0 || block > ARRAY_SIZE(sRevealedBlockTilemapValues))
                continue;
            appearance = sRevealedBlockTilemapValues[block];
            if (appearance == 0)
                continue;

            gBgPointersAndDimensions.backgrounds[1].pDecomp[position] = appearance;
        }
    }
}
