#include "macros.h"

#include "structs/rando.h"

#include "constants/rando.h"

const struct Seed sRandoSeed = {
    .playerNumber = 0,
    .playerName = {},
    .seedName = {},

    .options = {
        .goal = GOAL_MECHA_RIDLEY,
        .unknownItemsAlwaysUsable = FALSE,
        .skipChozodiaStealth = FALSE,
        .usePowerBombsWithoutBomb = FALSE,
        .removeGravityHeatResistance = FALSE,
    }
};

const struct StartingInventory sRandoStartingInventory = {
    .energyTanks = 0,
    .missileTanks = 0,
    .superMissileTanks = 0,
    .powerBombTanks = 0,
    .beamBombs = 0,
    .suitMisc = 0,
};

const struct PlacedItem sPlacedItems[100] = {};
