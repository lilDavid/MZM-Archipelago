#ifndef RANDO_STRUCT_H
#define RANDO_STRUCT_H

#include "types.h"

// Structs

struct Seed {
    u16 playerNumber;
    u8 playerName[64];
    u8 seedName[64];
};

// Globals

extern struct Seed gRandoSeed;

#endif /* SAMUS_STRUCT_H */
