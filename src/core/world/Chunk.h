//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_CHUNK_H
#define RECLAIMER_CHUNK_H

#include <vector>
#include <glm/vec2.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>

#include "core/Constants.h"
#include "TileType.h"
#include "Tile.h"


class World;


class TerrainMesh;


class Chunk {
public:
    friend class boost::serialization::access;

    int posX;
    int posZ;
    World *world;
    TerrainMesh *mesh;

    Chunk(World *world, int x, int z);
    ~Chunk();

    Tile *getTile(int x, int z);
    void setTile(int x, int z, int value);
    void setTile(int x, int z, TileType tile);

    void updateMesh();

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & tiles;
    }
protected:
private:
    Tile tiles[constants::CHUNK_SIZE][constants::CHUNK_SIZE];
    Chunk();

    void SetTileHeight(int x, int z, int height);
};

BOOST_CLASS_VERSION(Chunk, 0)

#endif //RECLAIMER_CHUNK_H
