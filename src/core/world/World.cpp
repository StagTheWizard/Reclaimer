//
// Created by montgomery anderson on 18/07/17.
//

#include "World.h"

#include <glm/vec2.hpp>
#include <glad/glad.h>

#include "Chunk.h"
#include "TileTypes.h"
#include "Tile.h"


World::World(int depth, int width) {
    this->depth = depth;
    this->width = width;
    // Generate the chunk map of set size
    this->chunks.resize(depth);

    // Initialise the chunks
    for (int z = 0; z < depth; z++) {
        this->chunks[z].resize(width);
        for (int x = 0; x < width; x++) {
            chunks[z][x] = new Chunk(this, x, z);
        }
    }

    // Generate the initial meshes
    for (int z = 0; z < depth; z++) {
        this->chunks[z].resize(width);
        for (int x = 0; x < width; x++) {
            chunks[z][x]->updateMesh();
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
    if (meshOutdated)
        updateMesh();
}


void World::updateMesh() {
    if (terrainMesh)
        delete terrainMesh;
    terrainMesh = new TerrainMesh();
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            terrainMesh->append(chunks[z][x]->mesh);
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
        return getChunk(chunkX, chunkZ)->getTile(x, z);
    } catch (std::out_of_range) {
        return new Tile(TileTypes::Void.id, x, z, 0);
    }

}
