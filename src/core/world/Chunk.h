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

    Chunk(World *world, int posX, int posZ);
    ~Chunk();

    Tile *getTile(int x, int z);
    void setTile(int x, int z, int value);
    void setTile(int x, int z, TileType tile);

    bool isModified();
    bool needsMeshRegenerated();

    void setLevelOfDetail(int lod);
    void updateMesh();

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & tiles;
    }
protected:
private:
    const float LOD_SEEM_HEIGHT = 0.0f;

    bool modified = false;
    bool regenerateMesh = true;
    int levelOfDetail = constants::LOD_1ST;

    Tile tiles[constants::CHUNK_SIZE][constants::CHUNK_SIZE];

    // Array of tile Ids for uniform rendering (may deprecate tiles array)
    int tileIds[constants::CHUNK_SIZE][constants::CHUNK_SIZE];

    Chunk();

    void setTileHeight(int x, int z, int height);
    glm::vec3 getPointNormal(int x, int z);
};

BOOST_CLASS_VERSION(Chunk, 0)

#endif //RECLAIMER_CHUNK_H
