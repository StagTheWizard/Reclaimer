//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_CHUNK_H
#define RECLAIMER_CHUNK_H

#include <vector>
#include <glm/vec2.hpp>

#include "core/Constants.h"
#include "TileType.h"
#include "Tile.h"


class World;
class TerrainMesh;


class Chunk {
public:
    Chunk(World *world, int x, int z);
    ~Chunk();

    Tile * GetTile(int x, int z);

    void SetTile(int x, int z, int value);
    void SetTile(int x, int z, TileType tile);

    void UpdateMesh();

    TerrainMesh *mesh;
protected:
private:
    Tile tiles[constants::CHUNK_SIZE][constants::CHUNK_SIZE];

    World *world;

    int posX;
    int posZ;
    void SetTileHeight(int x, int z, int height);
};


#endif //RECLAIMER_CHUNK_H
