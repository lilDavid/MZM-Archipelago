#ifndef ZIPLINE_GENERATOR_DATA_H
#define ZIPLINE_GENERATOR_DATA_H

#include "types.h"
#include "oam.h"

extern const u32 sZiplineGeneratorGfx[1124];
extern const u16 sZiplineGeneratorPal[64];

extern const struct FrameData sZiplineGeneratorPartOam_ConductorDeactivated[2];
extern const struct FrameData sZiplineGeneratorOam_Deactivated[2];
extern const struct FrameData sZiplineGeneratorPartOam_ConductorActivating[7];
extern const struct FrameData sZiplineGeneratorOam_Activating[7];
extern const struct FrameData sZiplineGeneratorPartOam_ConductorActivated[7];
extern const struct FrameData sZiplineGeneratorOam_Activated[7];
extern const struct FrameData sZiplineGeneratorPartOam_MorphSymbolActivating[7];
extern const struct FrameData sZiplineGeneratorPartOam_MorphSymbolActivated[9];
extern const struct FrameData sZiplineGeneratorPartOam_ElectricityActivating[12];

#endif /* ZIPLINE_GENERATOR_DATA_H */
