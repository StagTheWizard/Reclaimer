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
            chunks[z][x]->UpdateMesh();
        }
    }
}


World::~World() {}


int World::Depth() {
    return this->depth;
}


int World::Width() {
    return this->width;
}


void World::Update() {
    if (meshOutdated)
        UpdateMesh();
}


void World::UpdateMesh() {
    terrainMesh = new TerrainMesh();
    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            terrainMesh->append(chunks[z][x]->mesh);
        }
    }
}


void World::Render() {
//    GLuint vbo[2];
//    glGenBuffers(2, vbo);
//
//    // First VBO
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &terrainMesh->verticies[0], GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//    // Second VBO
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), &terrainMesh->edges[0], GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

//    glPatchParameteri(GL_PATCH_VERTICES, 9);
//    glDrawArrays(GL_PATCHES, 0);
}


Chunk *World::getChunk(int x, int z) {
    if (x < 0 || x > width)
        throw std::out_of_range("Attempted to access chunk outside of world width");
    if (z < 0 || z < depth)
        throw std::out_of_range("Attempted to access chunk outside of world depth");

    return chunks[z][x];
}


Tile *World::getTile(int chunkX, int chunkZ, int x, int z) {
    try {
        return getChunk(chunkX, chunkZ)->GetTile(x, z);
    } catch (std::out_of_range) {
        return new Tile(TileTypes::Void.id, x, z, 0);
    }

}
