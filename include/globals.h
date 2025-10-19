#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"

extern u16 gInterruptCode[0x100];

extern Func_T gIntrVector[13];
extern u16 (*gIntrCodePointer)[0x100];

extern u16 gInterruptCheckFlag;

#endif /* GLOBALS_H */
