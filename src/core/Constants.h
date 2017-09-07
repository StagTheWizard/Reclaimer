//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_CONSTANTS_H
#define RECLAIMER_CONSTANTS_H


#include <string>

namespace constants {
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 960;

    const std::string VERSION = "0.1";
    const std::string WINDOW_TITLE = "Reclaimer " + VERSION;


    const int WORLD_WIDTH = 64;
    const int WORLD_DEPTH = 64;
    const int WORLD_HEIGHT = 8;
    const int CHUNK_SIZE = 32;
    const int TILE_SIZE = 1;

    static int LOAD_DISTANCE = 14;
    static int UNLOAD_DISTANCE = 16;

//    const int LOD_1ST = 1;
//    const int LOD_2ND = 2;
//    const int LOD_3RD = 4;
//    const int LOD_4TH = 8;
//    const int LOD_5TH = 8;
//    static int LOD_1ST_DISTANCE = 2;
//    static int LOD_2ND_DISTANCE = 3;
//    static int LOD_3RD_DISTANCE = 4;
//    static int LOD_4TH_DISTANCE = 5;

    const int LOD_1ST = 1;
    const int LOD_2ND = 2;
    const int LOD_3RD = 4;
    const int LOD_4TH = 6;
    const int LOD_5TH = 8;
    static int LOD_1ST_DISTANCE = 4;
    static int LOD_2ND_DISTANCE = 6;
    static int LOD_3RD_DISTANCE = 8;
    static int LOD_4TH_DISTANCE = 10;
}

#endif //RECLAIMER_CONSTANTS_H
