#include "macros.h"
#include "types.h"

#include "structs/rando.h"

#include "constants/rando.h"
#include "constants/samus.h"

const struct Seed sRandoSeed = {
    .playerName = {},
    .seedName = {},

    .options = {
        .difficulties = ALLOW_NORMAL | ALLOW_HARD,

        .removeGravityHeatResistance = FALSE,
        .usePowerBombsWithoutBomb = FALSE,

        .skipChozodiaStealth = FALSE,
        .startWithMaps = FALSE,

        .skipTourianOpening = FALSE,
        .elevatorSpeed = (PIXEL_SIZE * 2),
    }
};

const struct StartingInventory sRandoStartingInventory = {
    .energyTanks = 0,
    .missileTanks = 0,
    .superMissileTanks = 0,
    .powerBombTanks = 0,
    .beamBombs = BBF_NONE,
    .suitMisc = SMF_NONE,
    .customItems = CIF_NONE,
};

const struct PlacedItem sPlacedItems[RC_COUNT] = {};
