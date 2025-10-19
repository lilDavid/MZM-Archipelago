#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "types.h"
#include "structs/multiboot.h"

void MultiBootInit(struct MultiBootData* pMultiBoot);
u32 MultiBootMain(struct MultiBootData* pMultiBoot);
void MultiBootStartProbe(struct MultiBootData* pMultiBoot);
void MultiBootStartParent(struct MultiBootData* pMultiBoot, const u8* src, s32 length, u8 palette_color, s8 palette_speed);
u32 MultiBootCheckComplete(struct MultiBootData* pMultiBoot);

#endif /* MULTIBOOT_H */
