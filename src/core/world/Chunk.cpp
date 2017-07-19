//
// Created by montgomery anderson on 18/07/17.
//

#include "Chunk.h"

#include "TileTypes.h"
#include "World.h"
#include "TerrainMesh.h"


Chunk::Chunk(World *world, int x, int z) {
    this->world = world;
    this->posX = x;
    this->posZ = z;

    // Populate the tile array with dirt by default
    for (int x = 0; x < constants::CHUNK_SIZE; x++) {
        for (int z = 0; z < constants::CHUNK_SIZE; z++) {
            this->tiles[z][x] = Tile { TileTypes::Dirt.id, x, z, 0 };
        }
    }
}


Chunk::~Chunk() {}


Tile *Chunk::GetTile(int x, int z) {
    return &tiles[z][x];
}


void Chunk::SetTile(int x, int z, int typeId) {
    tiles[z][x].typeId = typeId;
    UpdateMesh();
}


void Chunk::SetTileHeight(int x, int z, int height) {
    this->tiles[z][x].y = height;
}


void Chunk::SetTile(int x, int z, TileType tile) {
    SetTile(z, x, tile.id);
}


void Chunk::UpdateMesh() {
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

            glm::vec3 pN = glm::vec3(pX, pZ + halfTile, 0.5 * pHeight + 0.5 * heightNorth);
            glm::vec3 pE = glm::vec3(pX + halfTile, pZ, 0.5 * pHeight + 0.5 * heightEast);
            glm::vec3 pS = glm::vec3(pX, pZ - halfTile, 0.5 * pHeight + 0.5 * heightSouth);
            glm::vec3 pW = glm::vec3(pX - halfTile, pZ, 0.5 * pHeight + 0.5 * heightWest);

            mesh->verticies.push_back(pN);
            mesh->verticies.push_back(pE);
            mesh->verticies.push_back(pS);
            mesh->verticies.push_back(pW);

            long i_pN = mesh->verticies.size() - 4;
            long i_pE = mesh->verticies.size() - 3;
            long i_pS = mesh->verticies.size() - 2;
            long i_pW = mesh->verticies.size() - 1;
            mesh->edges.push_back(glm::vec2(i_pN, i_pE));
            mesh->edges.push_back(glm::vec2(i_pE, i_pS));
            mesh->edges.push_back(glm::vec2(i_pS, i_pW));
            mesh->edges.push_back(glm::vec2(i_pW, i_pE));
        }
    }
}
