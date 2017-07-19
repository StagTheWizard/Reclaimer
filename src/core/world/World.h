//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_WORLD_H
#define RECLAIMER_WORLD_H


#include <vector>
#include <glm/vec2.hpp>
#include "TerrainMesh.h"


class Chunk;
class TileType;
class Tile;


class World {
public:
    World(int depth, int width);
    ~World();

    void Update();
    void Render();

    bool meshOutdated;
    void UpdateMesh();

    int Depth();
    int Width();
    Chunk* getChunk(int x, int z);
    Tile* getTile(int chunkX, int chunkZ, int x, int z);
protected:
private:
    int depth;
    int width;

    std::vector<std::vector<Chunk*>> chunks;
    TerrainMesh *terrainMesh;
};


#endif //RECLAIMER_WORLD_H
