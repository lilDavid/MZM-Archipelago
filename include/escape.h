#ifndef ESCAPE_H
#define ESCAPE_H

#include "types.h"

#include "constants/escape.h"

// Functions

Escape EscapeDetermineTimer(void);
boolu8 EscapeCheckHasEscaped(void);
void EscapeUpdateOam(void);
void EscapeCheckReloadGraphics(void);
void EscapeStart(void);
void EscapeSetTimer(void);
void EscapeUpdateTimer(void);

#endif /* ESCAPE_H */
