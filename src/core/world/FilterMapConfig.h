//
// Created by montgomery anderson on 21/07/17.
//

#ifndef RECLAIMER_FILTERMAPCONFIG_H
#define RECLAIMER_FILTERMAPCONFIG_H

#include "extensions/fastnoise/FastNoise.h"

/**
 * Simple configuration data struct for storing noise map configuration data for FastNoise.
 */
struct FilterMapConfig {
    int seed;
    FN_DECIMAL frequency = 0.02;
    FastNoise::Interp interp = FastNoise::Quintic;
    FastNoise::NoiseType type = FastNoise::Simplex;

    int fractalOctaves = 6;
    FN_DECIMAL fractalLacunarity = 2.0;
    FN_DECIMAL fractalGain = 0.5;
    FastNoise::FractalType fractalType = FastNoise::FBM;

    FastNoise::CellularDistanceFunction cellularDistanceFunction = FastNoise::Euclidean;
    FastNoise::CellularReturnType cellularReturnType = FastNoise::CellValue;
    int cellularDistanceIndex0 = 0;
    int cellularDistanceIndex1 = 1;
    FN_DECIMAL cellularJitter = 0.45;

    FN_DECIMAL gradientPerturbAmp = 1.0;
};

#endif //RECLAIMER_FILTERMAPCONFIG_H
