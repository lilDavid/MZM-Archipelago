#ifndef HUD_STRUCT_H
#define HUD_STRUCT_H

#include "types.h"
#include "macros.h"

// Defines

MAKE_ENUM(u8, HudHighlightStatus) {
    HIGHLIGHT_STATUS_NOT_HIGHLIGHTED,
    HIGHLIGHT_STATUS_SELECTED,
    HIGHLIGHT_STATUS_HIGHLIGHTED
};

// Structs

struct HudDigits {
    u8 ones;
    u8 tens;
    u8 hundreds;
    u8 thousands;
};

// Globals

extern boolu8 gHideHud;
extern HudHighlightStatus gMissileHighlightStatus;
extern HudHighlightStatus gPowerBombHighlightStatus;
extern HudHighlightStatus gSuperMissileHighlightStatus;

extern struct HudDigits gEnergyDigits;
extern struct HudDigits gMaxEnergyDigits;
extern struct HudDigits gMissileDigits;
extern struct HudDigits gPowerBombDigits;
extern struct HudDigits gSuperMissileDigits;

extern u8 gEnergyRefillAnimation;
extern u8 gMissileRefillAnimation;
extern u8 gSuperMissileRefillAnimation;
extern u8 gPowerBombRefillAnimation;

extern u8 gAmmoDigitsGfx[64];

#endif /* HUD_STRUCT_H */
