//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TILETYPES_H
#define RECLAIMER_TILETYPES_H

#include "TileType.h"

namespace TileTypes {
    static const TileType Void = {0, "Void"};
    static const TileType Dirt = {1, "Dirt"};

    static const TileType Map[2] = {
            Void,
            Dirt
    };
}

#endif //RECLAIMER_TILETYPES_H
