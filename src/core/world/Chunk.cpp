//
// Created by montgomery anderson on 18/07/17.
//

#include "Chunk.h"

#include "TileTypes.h"
#include "World.h"
#include "TerrainMesh.h"


Chunk::Chunk() {}


Chunk::Chunk(World *world, int x, int z) {
    this->world = world;
    this->posX = x;
    this->posZ = z;

    // Populate the tile array with dirt by default
    for (int x = 0; x < constants::CHUNK_SIZE; x++) {
        for (int z = 0; z < constants::CHUNK_SIZE; z++) {
            this->tiles[z][x] = Tile {TileTypes::Dirt.id, x, z, 0};
        }
    }
}


Chunk::~Chunk() {
    delete mesh;
}


Tile *Chunk::getTile(int x, int z) {
    return &tiles[z][x];
}


void Chunk::setTile(int x, int z, int typeId) {
    tiles[z][x].typeId = typeId;
    updateMesh();
}


void Chunk::SetTileHeight(int x, int z, int height) {
    this->tiles[z][x].y = height;
}


void Chunk::setTile(int x, int z, TileType tile) {
    setTile(z, x, tile.id);
}


void Chunk::updateMesh() {
    this->mesh = new TerrainMesh();

    int cX = posX * constants::CHUNK_SIZE * constants::TILE_SIZE;
    int cZ = posZ * constants::CHUNK_SIZE * constants::TILE_SIZE;
    float halfTile = (float) (0.5 * constants::TILE_SIZE);

    for (int x = 0; x < constants::CHUNK_SIZE; x++) {
        int pX = cX + x * constants::TILE_SIZE;

        for (int z = 0; z < constants::CHUNK_SIZE; z++) {
            int pZ = cZ + z * constants::TILE_SIZE;
            int pHeight = tiles[z][x].y;
            int heightNorth;
            // if we are on the northern border
            if (z == constants::CHUNK_SIZE - 1)
                heightNorth = world->getTile(posX, posZ + 1, x, 0)->y;
            else
                heightNorth = tiles[z][x].y;

            int heightEast;
            // if we are on the eastern border
            if (x == constants::CHUNK_SIZE - 1)
                heightEast = world->getTile(posX + 1, posZ, 0, z)->y;
            else
                heightEast = tiles[z][x].y;

            int heightSouth;
            // if we are on the southern border
            if (z == 0)
                heightSouth = world->getTile(posX, posZ - 1, x, constants::CHUNK_SIZE - 1)->y;
            else
                heightSouth = tiles[z][x].y;

            int heightWest;
            // if we are on the western border
            if (x == 0)
                heightWest = world->getTile(posX - 1, posZ, constants::CHUNK_SIZE - 1, z)->y;
            else
                heightWest = tiles[z][x].y;

            glm::vec3 pN = glm::vec3(pX + halfTile, 0.5 * pHeight + 0.5 * heightNorth, pZ + halfTile);
            glm::vec3 pE = glm::vec3(pX + halfTile, 0.5 * pHeight + 0.5 * heightEast, pZ - halfTile);
            glm::vec3 pS = glm::vec3(pX - halfTile, 0.5 * pHeight + 0.5 * heightSouth, pZ - halfTile);
            glm::vec3 pW = glm::vec3(pX - halfTile, 0.5 * pHeight + 0.5 * heightWest, pZ + halfTile);

            mesh->vertices.push_back(pN);
            mesh->vertices.push_back(pW);
            mesh->vertices.push_back(pS);
            mesh->vertices.push_back(pS);
            mesh->vertices.push_back(pE);
            mesh->vertices.push_back(pN);

//            GLuint i_pN = (GLuint) mesh->vertices.size() - 4;
//            GLuint i_pW = (GLuint) mesh->vertices.size() - 3;
//            GLuint i_pS = (GLuint) mesh->vertices.size() - 2;
//            GLuint i_pE = (GLuint) mesh->vertices.size() - 1;
//            mesh->elements.push_back(i_pN);
//            mesh->elements.push_back(i_pW);
//            mesh->elements.push_back(i_pS);
//            mesh->elements.push_back(i_pN);
//            mesh->elements.push_back(i_pS);
//            mesh->elements.push_back(i_pE);
        }
    }
}