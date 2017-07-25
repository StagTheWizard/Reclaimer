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

    updateMesh();
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

    unsigned int i = 0;
    for (int x = 0; x < constants::CHUNK_SIZE; x++) {
        float pX = cX + x * constants::TILE_SIZE;

        for (int z = 0; z < constants::CHUNK_SIZE; z++) {
            float pZ = cZ + z * constants::TILE_SIZE;
            float y = tiles[z][x].y;
            glm::vec3 p = glm::vec3(pX, y, pZ);
            mesh->vertices.push_back(p);
            if (x != 0 && z != 0) {
                // Generate triangle elements using indices of E, S & W points
                unsigned int iWest = i - constants::CHUNK_SIZE;
                unsigned int iSouth = i - constants::CHUNK_SIZE - 1;
                unsigned int iEast = i - 1;

                mesh->elements.push_back(i);
                mesh->elements.push_back(iSouth);
                mesh->elements.push_back(iWest);

                mesh->elements.push_back(i);
                mesh->elements.push_back(iEast);
                mesh->elements.push_back(iSouth);
            }

            i++;
        }
    }
    unsigned int iLastInsideVert = i - 1;

    // Create one more strip to join with NW, N, NE chunks (if not null)
    // Firstly create the NW strip (if NW chunk exists / loaded)
    Chunk* chunkNW = world->tryGetChunk(posX + 1, posZ);
    if (chunkNW != NULL) {
        float pX = cX + constants::CHUNK_SIZE;
        int x = constants::CHUNK_SIZE - 1;
        for (int z = 0; z < constants::CHUNK_SIZE; z++) {
            float pZ = cZ + z * constants::TILE_SIZE;
            glm::vec3 p = glm::vec3(pX, chunkNW->getTile(0, z)->y, pZ);
            mesh->vertices.push_back(p);

            if (z != 0) {
                // Generate triangle elements using indices of E, S & W points
                unsigned int iWest = i - 1;
                unsigned int iEast = x * constants::CHUNK_SIZE + z;
                unsigned int iSouth = x * constants::CHUNK_SIZE + (z - 1);

                mesh->elements.push_back(i);
                mesh->elements.push_back(iWest);
                mesh->elements.push_back(iSouth);

                mesh->elements.push_back(i);
                mesh->elements.push_back(iSouth);
                mesh->elements.push_back(iEast);
            }

            i++;
        }
    }
    unsigned int iLastNW = i - 1;
    // Then create the NE strip (if NE chunk exists / loaded)
    Chunk* chunkNE = world->tryGetChunk(posX, posZ + 1);
    if (chunkNE != NULL) {
        float pZ = cZ + constants::CHUNK_SIZE;
        int z = constants::CHUNK_SIZE - 1;
        for (int x = 0; x < constants::CHUNK_SIZE; x++) {
            float pX = cX + x * constants::TILE_SIZE;
            glm::vec3 p = glm::vec3(pX, chunkNE->getTile(x, 0)->y, pZ);
            mesh->vertices.push_back(p);

            if (x != 0) {
                // Generate triangle elements using indices of E, S & W points
                unsigned int iWest = x * constants::CHUNK_SIZE + z;
                unsigned int iSouth = (x - 1) * constants::CHUNK_SIZE + z;
                unsigned int iEast = i - 1;

                mesh->elements.push_back(i);
                mesh->elements.push_back(iWest);
                mesh->elements.push_back(iSouth);

                mesh->elements.push_back(i);
                mesh->elements.push_back(iSouth);
                mesh->elements.push_back(iEast);
            }

            i++;
        }
    }
    unsigned int iLastNE = i - 1;
    // Lastly create the Northern most point using the final verts from both
    // (if both NW & NE chunks are loaded)
    Chunk* chunkN = world->tryGetChunk(posX + 1, posZ + 1);
    if (chunkNW != NULL && chunkNE != NULL && chunkN != NULL) {
        float pX = cX + constants::CHUNK_SIZE;
        float pZ = cZ + constants::CHUNK_SIZE;
        glm::vec3 p = glm::vec3(pX, chunkN->getTile(0, 0)->y, pZ);
        mesh->vertices.push_back(p);

        unsigned int iEast = iLastNE;
        unsigned int iSouth = iLastInsideVert;
        unsigned int iWest = iLastNW;

        mesh->elements.push_back(i);
        mesh->elements.push_back(iSouth);
        mesh->elements.push_back(iEast);

        mesh->elements.push_back(i);
        mesh->elements.push_back(iWest);
        mesh->elements.push_back(iSouth);
    }

}
