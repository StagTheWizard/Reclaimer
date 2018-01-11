//
// Created by montgomery anderson on 18/07/17.
//

#include "World.h"

#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

#include "Chunk.h"
#include "TileTypes.h"
#include "Tile.h"
#include "extensions/geometry/SpacialChecks.h"


World::World(int depth, int width, int seed) {
    this->depth = depth;
    this->width = width;
    this->masterSeed = seed;

    this->noiseGenerator = new FastNoise();

    layer0.seed = masterSeed;
    this->noiseGenerator->SetSeed(layer0.seed);
    this->noiseGenerator->SetFrequency(layer0.frequency);
    this->noiseGenerator->SetInterp(layer0.interp);
    this->noiseGenerator->SetNoiseType(layer0.type);
    this->noiseGenerator->SetFractalOctaves(layer0.fractalOctaves);
    this->noiseGenerator->SetFractalLacunarity(layer0.fractalLacunarity);
    this->noiseGenerator->SetFractalGain(layer0.fractalGain);
    this->noiseGenerator->SetFractalType(layer0.fractalType);
    this->noiseGenerator->SetCellularDistanceFunction(layer0.cellularDistanceFunction);
    this->noiseGenerator->SetCellularReturnType(layer0.cellularReturnType);
    this->noiseGenerator->SetCellularNoiseLookup(this->noiseGenerator);
    this->noiseGenerator->SetCellularDistance2Indices(layer0.cellularDistanceIndex0, layer0.cellularDistanceIndex1);
    this->noiseGenerator->SetCellularJitter(layer0.cellularJitter);
    this->noiseGenerator->SetGradientPerturbAmp(layer0.gradientPerturbAmp);


    if (!boost::filesystem::exists(saveFolder))
        boost::filesystem::create_directory(saveFolder);

    if (!boost::filesystem::exists(chunkFolder))
        boost::filesystem::create_directory(chunkFolder);

    // Generate the chunk map of set size
    this->chunks.resize(depth);
    // Initialise the chunks
    for (int z = 0; z < depth; z++) {
        this->chunks[z].resize(width);
        for (int x = 0; x < width; x++) {
            chunks[z][x] = NULL;
        }
    }
}


World::~World() {}


int World::getDepth() {
    return this->depth;
}


int World::getWidth() {
    return this->width;
}


void World::update(glm::vec3 cameraPos) {
    updateLoading(cameraPos);
    updateLod(cameraPos);
}


Chunk *World::getChunk(int x, int z) {
    if (x < 0 || x >= width)
        throw std::out_of_range("Attempted to access chunk outside of world width");
    if (z < 0 || z >= depth)
        throw std::out_of_range("Attempted to access chunk outside of world depth");

    return chunks[z][x];
}


Chunk *World::tryGetChunk(int x, int z) {
    Chunk* chunk = NULL;
    try {
        chunk = getChunk(x, z);
    } catch (std::out_of_range e) {
        chunk = NULL;
    }
    return chunk;
}


Tile *World::getTile(int chunkX, int chunkZ, int x, int z) {
    try {
        Chunk *chunk = getChunk(chunkX, chunkZ);
        if (chunk == NULL)
            return new Tile(TileTypes::Void.id, x, z, 0.0);
        else
            return chunk->getTile(x, z);
    } catch (std::out_of_range) {
        return new Tile(TileTypes::Void.id, x, z, 0.0);
    }
}


void World::updateLoading(glm::vec3 cameraPos) {
    for (int z = depth - 1; z >= 0; z--) {
        for (int x = width - 1; x >= 0; x--) {
            Chunk* chunk = tryGetChunk(x, z);
            bool loaded = false;
            if (chunk == NULL && chunkInRadius(x, z, cameraPos, constants::LOAD_DISTANCE)) {
                loadChunk(x, z);
                loaded = true;
            }
            bool unloaded = false;
            if (chunk != NULL && !chunkInRadius(x, z, cameraPos, constants::UNLOAD_DISTANCE)) {
                unloadChunk(x, z);
                unloaded = true;
            }
            if (loaded || unloaded) {
                // When we load or unload a new chunk we need to update the mesh of S, SE, SW chunks
                // TODO implement a chunk-seeming strip addition/removal method to the mesh
                Chunk* cSE = tryGetChunk(x - 1, z);
                if (cSE != NULL) cSE->updateMesh();
                Chunk* cSW = tryGetChunk(x, z - 1);
                if (cSW != NULL) cSW->updateMesh();
                Chunk* cS = tryGetChunk(x - 1, z - 1);
                if (cS != NULL) cS->updateMesh();
            }
        }
    }
}


void World::updateLod(glm::vec3 cameraPos) {
    for (int z = depth - 1; z >= 0; z--) {
        for (int x = width - 1; x >= 0; x--) {
            Chunk* chunk = tryGetChunk(x, z);
            if (chunk != NULL) {
                if (chunkInRadius(x, z, cameraPos, constants::LOD_1ST_DISTANCE))
                    chunk->setLevelOfDetail(constants::LOD_1ST);
                else if (chunkInRadius(x, z, cameraPos, constants::LOD_2ND_DISTANCE))
                    chunk->setLevelOfDetail(constants::LOD_2ND);
                else if (chunkInRadius(x, z, cameraPos, constants::LOD_3RD_DISTANCE))
                    chunk->setLevelOfDetail(constants::LOD_3RD);
                else if (chunkInRadius(x, z, cameraPos, constants::LOD_4TH_DISTANCE))
                    chunk->setLevelOfDetail(constants::LOD_4TH);
                else
                    chunk->setLevelOfDetail(constants::LOD_5TH);
            }
        }
    }
}


void World::saveChunk(int x, int z) {
    saveChunk(getChunk(x, z));
}


void World::saveChunk(Chunk* chunk) {
    std::string fileName = getChunkFileName(chunk->posX, chunk->posZ);
    std::string fileLocation = chunkFolder + fileName;

    std::ofstream outputFileStream = std::ofstream(fileLocation);
    boost::archive::text_oarchive outputArchive(outputFileStream);
    outputArchive << chunk;
}


bool World::loadChunk(int x, int z) {
    // Check if it has persisted data
    if (chunkHasSaveData(x, z)) {
        std::string fileName = getChunkFileName(x, z);
        std::string fileLocation = chunkFolder + fileName;

        std::ifstream inputFileStream = std::ifstream(fileLocation);
        boost::archive::text_iarchive inputArchive(inputFileStream);
        chunks[z][x] = new Chunk(this, x, z);
        // Load out the tiles
        inputArchive >> chunks[z][x];
        // Update memory relevant values
        chunks[z][x]->world = this;
        // PosX & Z are encoding in the filename, update from that connection
        chunks[z][x]->posX = x;
        chunks[z][x]->posZ = z;
    } else {
        // otherwise generate a bare chunk
        chunks[z][x] = new Chunk(this, x, z);
    }
}


bool World::unloadChunk(int x, int z) {
    Chunk *chunk = getChunk(x, z);
    return unloadChunk(chunk);
}


bool World::unloadChunk(Chunk* chunk) {
    if (chunk->isModified()) {
        saveChunk(chunk);
    }

    chunks[chunk->posZ][chunk->posX] = NULL;
    delete chunk;
}


std::string World::getChunkFileName(int x, int z) {
    return std::to_string(x) + "," + std::to_string(z) + ".bin";
}


bool World::chunkHasSaveData(int x, int z) {
    std::string fileName = getChunkFileName(x, z);
    std::string fileLocation = chunkFolder + fileName;
    return boost::filesystem::exists(fileLocation);
}


double World::chunkVerticesCount() {
    double count = 0;
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            Chunk* chunk = tryGetChunk(x, z);
            if (chunk != NULL)
                count += chunk->mesh->vertices.size();
        }
    }
    return count;
}


bool World::chunkInRadius(int x, int z, glm::vec3 centre, int radius) {
    float chunkCentreX = x * constants::CHUNK_SIZE + 0.5f * constants::CHUNK_SIZE;
    float chunkCentreZ = z * constants::CHUNK_SIZE + 0.5f * constants::CHUNK_SIZE;
    float worldRadius = static_cast<float>(radius * constants::CHUNK_SIZE);

    return extensions::withinSquareRadius(chunkCentreX, chunkCentreZ, centre.x, centre.z, worldRadius);
}
