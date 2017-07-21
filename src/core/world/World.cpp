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

#include "Chunk.h"
#include "TileTypes.h"
#include "Tile.h"


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
            if (chunkHasSaveData(x, z))
                loadChunk(x, z);
            else
                chunks[z][x] = new Chunk(this, x, z);
        }
    }

    this->meshOutdated = true;
}


World::~World() {}


int World::getDepth() {
    return this->depth;
}


int World::getWidth() {
    return this->width;
}


void World::update() {
    // We no longer generate world wide meshes but chunk-specific meshes
    if (meshOutdated)
        updateMesh();
}


void World::updateMesh() {
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            if (chunks[z][x] != NULL)
                chunks[z][x]->updateMesh();
        }
    }
    meshOutdated = false;
}


Chunk *World::getChunk(int x, int z) {
    if (x < 0 || x >= width)
        throw std::out_of_range("Attempted to access chunk outside of world width");
    if (z < 0 || z >= depth)
        throw std::out_of_range("Attempted to access chunk outside of world depth");

    return chunks[z][x];
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
    if (!chunkHasSaveData(x, z)) return false;

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
            if (chunks[z][x] != NULL)
                count += chunks[z][x]->mesh->vertices.size();
        }
    }
    return count;
}