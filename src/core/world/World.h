//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_WORLD_H
#define RECLAIMER_WORLD_H


#include <vector>
#include <glm/vec2.hpp>
#include <string>

#include "TerrainMesh.h"
#include "extensions/fastnoise/FastNoise.h"
#include "core/world/FilterMapConfig.h"


class Chunk;
class TileType;
class Tile;


class World {
public:
    std::string name = "world 1";
    std::string saveFolder = "saves/" + name + "/";
    std::string chunkFolder = saveFolder + "chunks/";

    int masterSeed;
    FilterMapConfig layer0 = FilterMapConfig();
    FastNoise *noiseGenerator = NULL;

    TerrainMesh *terrainMesh = NULL;

    World(int depth, int width, int seed = rand());
    ~World();

    void update(glm::vec3 cameraPos);

    int getDepth();
    int getWidth();

    Chunk* getChunk(int x, int z);
    Chunk* tryGetChunk(int x, int z);

    double chunkVerticesCount();

    Tile* getTile(int chunkX, int chunkZ, int x, int z);

protected:
private:
    int depth;
    int width;

    std::vector<std::vector<Chunk*>> chunks;

    void updateLoading(glm::vec3 cameraPos);
    void updateLod(glm::vec3 cameraPos);
    void updateMeshes();

    void saveChunk(int x, int z);
    void saveChunk(Chunk* chunk);
    bool loadChunk(int x, int z);

    bool unloadChunk(int x, int z);
    bool unloadChunk(Chunk* chunk);

    std::string getChunkFileName(int x, int z);
    bool chunkHasSaveData(int x, int z);

    bool chunkInRadius(int x, int z, glm::vec3 centre, int radius);
};


#endif //RECLAIMER_WORLD_H
