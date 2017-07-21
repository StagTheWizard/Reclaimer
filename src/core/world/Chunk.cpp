//
// Created by montgomery anderson on 18/07/17.
//

#include "Chunk.h"

#include "TileTypes.h"
#include "World.h"
#include "TerrainMesh.h"


Chunk::Chunk() {}


Chunk::Chunk(World *world, int posX, int posZ) {
    this->world = world;
    this->posX = posX;
    this->posZ = posZ;

    // Populate the tile array with dirt by default
    int baseX = posX * constants::CHUNK_SIZE;
    int baseZ = posZ * constants::CHUNK_SIZE;
    for (int z = 0; z < constants::CHUNK_SIZE; z++) {
        for (int x = 0; x < constants::CHUNK_SIZE; x++) {
            float yGen = world->noiseGenerator->GetSimplexFractal(baseX + x, baseZ + z);
            float y = (yGen + 1) * static_cast<float>(constants::WORLD_HEIGHT / 2);
            this->tiles[z][x] = Tile(TileTypes::Dirt.id, x, z, y);
        }
    }
}


Chunk::~Chunk() {
    delete mesh;
}


bool Chunk::isModified() {
    return this->modified;
}


Tile *Chunk::getTile(int x, int z) {
    return &tiles[z][x];
}


void Chunk::setTile(int x, int z, int typeId) {
    if (tiles[z][x].typeId == typeId)
        return;
    tiles[z][x].typeId = typeId;
    modified = true;
    updateMesh();
}


void Chunk::setTileHeight(int x, int z, int height) {
    this->tiles[z][x].y = height;
}


void Chunk::setTile(int x, int z, TileType tile) {
    setTile(z, x, tile.id);
}


void Chunk::updateMesh() {
    this->mesh = new TerrainMesh();

    int cX = posX * constants::CHUNK_SIZE * constants::TILE_SIZE;
    int cZ = posZ * constants::CHUNK_SIZE * constants::TILE_SIZE;

    for (int x = 0; x < constants::CHUNK_SIZE; x++) {
        int pX = cX + x * constants::TILE_SIZE;

        for (int z = 0; z < constants::CHUNK_SIZE; z++) {
            int pZ = cZ + z * constants::TILE_SIZE;
            float pHeight = tiles[z][x].y;
            float heightNorth;
            float heightEast;
            float heightSouth;
            float heightWest;
            bool northWestEdge = z == constants::CHUNK_SIZE - 1;
            bool southEastEdge = z == 0;
            bool northEastEdge = x == constants::CHUNK_SIZE - 1;
            bool southWestEdge = x == 0;

            float hN, hE, hS, hW, hNE, hSE, hNW, hSW;

            // height NW
            if (northWestEdge) hNW = world->getTile(posX, posZ + 1, x, 0)->y;
            else hNW = tiles[z + 1][x].y;
            // height NE
            if (northEastEdge) hNE = world->getTile(posX + 1, posZ, 0, z)->y;
            else hNE = tiles[z][x + 1].y;
            // height SE
            if (southEastEdge) hSE = world->getTile(posX, posZ - 1, x, constants::CHUNK_SIZE - 1)->y;
            else hSE = tiles[z - 1][x].y;
            // height SW
            if (southWestEdge) hSW = world->getTile(posX - 1, posZ, constants::CHUNK_SIZE - 1, z)->y;
            else hSW = tiles[z][x - 1].y;



            // height N
            if (northWestEdge) { // posZ + 1
                if (northEastEdge) // posX + 1
                    hN = world->getTile(posX + 1, posZ + 1, 0, 0)->y;
                else // posX
                    hN = world->getTile(posX, posZ + 1, x + 1, 0)->y;
            } else {// posZ
                if (northEastEdge) // posX + 1
                    hN = world->getTile(posX + 1, posZ, 0, z + 1)->y;
                else // posX / inside this chunk
                    hN = tiles[z + 1][x + 1].y;
            }
            // height E
            if (northEastEdge) { // posX + 1
                if (southEastEdge) // posZ - 1
                    hE = world->getTile(posX + 1, posZ - 1, 0, constants::CHUNK_SIZE - 1)->y;
                else // posZ
                    hE = world->getTile(posX + 1, posZ, 0, z - 1)->y;
            } else { // posX + 1
                if (southEastEdge) // posZ - 1
                    hE = world->getTile(posX, posZ - 1, x + 1, constants::CHUNK_SIZE - 1)->y;
                else // poxZ / inside this chunk
                    hE = tiles[z - 1][x + 1].y;
            }
            // height S
            if (southWestEdge) { // posX - 1
                if (southEastEdge) // posZ - 1
                    hS = world->getTile(posX - 1, posZ - 1, constants::CHUNK_SIZE - 1,
                                                 constants::CHUNK_SIZE - 1)->y;
                else // posZ
                    hS = world->getTile(posX - 1, posZ, constants::CHUNK_SIZE - 1, z - 1)->y;
            } else { // posX
                if (southEastEdge) // posZ - 1
                    hS = world->getTile(posX, posZ - 1, x - 1, constants::CHUNK_SIZE - 1)->y;
                else // posZ / inside this chunk
                    hS = tiles[z - 1][x - 1].y;
            }
            // height W
            if (northWestEdge) { // posZ + 1
                if (southWestEdge) // posX - 1
                    hW = world->getTile(posX - 1, posZ + 1, constants::CHUNK_SIZE - 1, 0)->y;
                else // posX
                    hW = world->getTile(posX, posZ + 1, x - 1, 0)->y;
            } else { // posZ
                if (southWestEdge) // posX - 1
                    hW = world->getTile(posX - 1, posZ, constants::CHUNK_SIZE - 1, z + 1)->y;
                else // posX / inside this chunk
                    hW = tiles[z + 1][x - 1].y;
            }

            glm::vec3 pN = glm::vec3(pX + constants::TILE_SIZE,
                                     (pHeight + hN + hNE + hNW) / 4,
                                     pZ + constants::TILE_SIZE);
            glm::vec3 pE = glm::vec3(pX + constants::TILE_SIZE,
                                     (pHeight + hE + hNE + hSE) / 4,
                                     pZ);
            glm::vec3 pS = glm::vec3(pX,
                                     (pHeight + hS + hSE + hSW) / 4,
                                     pZ);
            glm::vec3 pW = glm::vec3(pX,
                                     (pHeight + hW + hNW + hSW) / 4,
                                     pZ + constants::TILE_SIZE);

            mesh->vertices.push_back(pN);
            mesh->vertices.push_back(pS);
            mesh->vertices.push_back(pW);
            mesh->vertices.push_back(pS);
            mesh->vertices.push_back(pN);
            mesh->vertices.push_back(pE);

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