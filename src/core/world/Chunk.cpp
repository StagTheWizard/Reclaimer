//
// Created by montgomery anderson on 18/07/17.
//

#include <glm/geometric.hpp>
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
            int typeId = TileTypes::Dirt.id;
            tiles[z][x] = Tile(typeId, x, z, y);
            tileIds[z][x] = typeId;
        }
    }

    this->regenerateMesh = true;
}


Chunk::~Chunk() {
    delete mesh;
}


bool Chunk::isModified() {
    return this->modified;
}


bool Chunk::needsMeshRegenerated() {
    return this->regenerateMesh;
}


Tile *Chunk::getTile(int x, int z) {
    return &tiles[z][x];
}


void Chunk::setTile(int x, int z, int typeId) {
    if (tiles[z][x].typeId == typeId)
        return;
    tiles[z][x].typeId = typeId;
    tileIds[z][x] = typeId;
    modified = true;
    regenerateMesh = true;
}


void Chunk::setTileHeight(int x, int z, int height) {
    this->tiles[z][x].y = height;
    this->regenerateMesh = true;
}


void Chunk::setTile(int x, int z, TileType tile) {
    this->setTile(z, x, tile.id);
    this->regenerateMesh = true;
}


void Chunk::setLevelOfDetail(int lod) {
    if (constants::CHUNK_SIZE % lod != 0 || lod == this->levelOfDetail) return;
    this->levelOfDetail = lod;
    this->regenerateMesh = true;
    // if the LOD is now less than a neighbour, update neighbouring chunks meshes with different LODs
    Chunk* chunkNW = world->tryGetChunk(posX + 1, posZ);
    if (chunkNW != NULL && chunkNW->levelOfDetail <= lod)
        chunkNW->regenerateMesh = true;
    Chunk* chunkNE = world->tryGetChunk(posX, posZ + 1);
    if (chunkNE != NULL && chunkNE->levelOfDetail <= lod)
        chunkNE->regenerateMesh = true;
    Chunk* chunkSW = world->tryGetChunk(posX, posZ - 1);
    if (chunkSW != NULL && chunkSW->levelOfDetail <= lod)
        chunkSW->regenerateMesh = true;
    Chunk* chunkSE = world->tryGetChunk(posX - 1, posZ);
    if (chunkSE != NULL && chunkSE->levelOfDetail <= lod)
        chunkSE->regenerateMesh = true;
}


void Chunk::updateMesh() {
    this->mesh = new TerrainMesh();

    int cX = posX * constants::CHUNK_SIZE * constants::TILE_SIZE;
    int cZ = posZ * constants::CHUNK_SIZE * constants::TILE_SIZE;

    Chunk* chunkNE = world->tryGetChunk(posX, posZ + 1);
    Chunk* chunkNW = world->tryGetChunk(posX + 1, posZ);
    Chunk* chunkSW = world->tryGetChunk(posX, posZ - 1);
    Chunk* chunkSE = world->tryGetChunk(posX - 1, posZ);
    unsigned int i = 0;
    for (int x = 0; x < constants::CHUNK_SIZE - levelOfDetail + 1; x += levelOfDetail) {
        float pX = cX + x * constants::TILE_SIZE;

        for (int z = 0; z < constants::CHUNK_SIZE - levelOfDetail + 1; z += levelOfDetail) {
            float pZ = cZ + z * constants::TILE_SIZE;
            float y = tiles[z][x].y;
            glm::vec3 p = glm::vec3(pX, y, pZ);
            // Check for LOD boundaries on edge vertices .. as p.y may need to be modified to prevent seams in LOD levels
            if (z == 0 && x < constants::CHUNK_SIZE
                && chunkSW != NULL && chunkSW->levelOfDetail > levelOfDetail) {
                /* if
                 * -- we are on the z boundary (excluding corners)
                 * -- and we are not on the edge of the map
                 * -- and the level of detail decreases
                 */
                if (x == constants::CHUNK_SIZE - levelOfDetail) {
                    if (chunkNW != NULL) {
                        double avg = (tiles[0][x - levelOfDetail].y + chunkNW->getTile(0, 0)->y) / 2.0f;
                        p.y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
//                    p.y = 0.0f;
                    }
                } else {
                    if ((x - levelOfDetail) % (levelOfDetail * 2) == 0) {
                        if (x > 0) {
                            double avg = (tiles[0][x - levelOfDetail].y + tiles[0][x + levelOfDetail].y) / 2.0f;
                            p.y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
//                        p.y = 0;
                        }
                    }
                }
            }
            if (x == 0 && z < constants::CHUNK_SIZE
                && chunkSE != NULL && chunkSE->levelOfDetail > levelOfDetail) {
                /* if
                 * -- we are on the x boundary (excluding corners)
                 * -- and we are not on the edge of the map
                 * -- and the level of detail decreases
                 *
                 * then we must seam the tear by making every second emitted vertex (vertex without equivalent vertex
                 * in neighbouring chunk) along the boundary's height equal to the average of it's emitted neighbours */
                if (z == constants::CHUNK_SIZE - levelOfDetail) {
                    if (chunkNE != NULL) {
                        double avg = (tiles[z - levelOfDetail][0].y + chunkNE->getTile(0, 0)->y) / 2.0f;
                        p.y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
//                    p.y = 0.0f;
                    }
                } else {
                    if ((z - levelOfDetail) % (levelOfDetail * 2) == 0) {
                        if (z > 0) {
                            double avg = (tiles[z - levelOfDetail][0].y + tiles[z + levelOfDetail][0].y) / 2.0f;
                            p.y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
//                        p.y = 0;
                        }
                    }
                }
            }
            mesh->vertices.push_back(p);
            mesh->normals.push_back(getPointNormal(x, z));

            // Generate a new line of elements each line par the edge
            if (x != 0 && z != 0) {
                // Generate triangle elements using indices of E, S & W points
                unsigned int iWest = i - (constants::CHUNK_SIZE / levelOfDetail);
                unsigned int iSouth = i - (constants::CHUNK_SIZE / levelOfDetail) - 1;
                unsigned int iEast = i - 1;

                mesh->elements.push_back(i);
                mesh->elements.push_back(iSouth);
                mesh->elements.push_back(iWest);

                mesh->elements.push_back(i);
                mesh->elements.push_back(iEast);
                mesh->elements.push_back(iSouth);
            } else {

            }

            i++;
        }
    }
    unsigned int iLastInsideVert = i - 1;

    // Create one more strip to join with NW, N, NE chunks (if not null)

    // Firstly create the NW strip (if NW chunk exists / loaded)
    if (chunkNW != NULL) {
        float pX = cX + constants::CHUNK_SIZE * constants::TILE_SIZE;
        for (int z = 0; z < constants::CHUNK_SIZE; z += levelOfDetail) {
            float pZ = cZ + z * constants::TILE_SIZE;
            glm::vec3 p = glm::vec3(pX, chunkNW->getTile(0, z)->y, pZ);
            // Check for LOD boundaries on edge vertices .. as p.y may need to be modified to prevent seams in LOD levels
            if (z != 0 && z < constants::CHUNK_SIZE
                && chunkNW->levelOfDetail > levelOfDetail) {
                /* if
                 * -- we are on the z boundary (excluding corners)
                 * -- and we are not on the edge of the map
                 * -- and the level of detail decreases
                 */
                if ((z - levelOfDetail) % (levelOfDetail * 2) == 0)
                    if (z + levelOfDetail < constants::CHUNK_SIZE) {
                        double avg = (chunkNW->getTile(0, z - levelOfDetail)->y + chunkNW->getTile(0, z + levelOfDetail)->y) / 2.0f;
                        p.y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
//                        p.y = 0;
                    }
            }
            mesh->vertices.push_back(p);
            mesh->normals.push_back(getPointNormal(constants::CHUNK_SIZE, z));

            if (z != 0) {
                // Generate triangle elements using indices of E, S & W points
                unsigned int iWest = i - 1;
                unsigned int iEast = pow((constants::CHUNK_SIZE / levelOfDetail), 2) -
                        (constants::CHUNK_SIZE / levelOfDetail - (z / levelOfDetail));
                unsigned int iSouth = iEast - 1;

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
    if (chunkNE != NULL) {
        float pZ = cZ + constants::CHUNK_SIZE;
        for (int x = 0; x < constants::CHUNK_SIZE; x += levelOfDetail) {
            float pX = cX + x * constants::TILE_SIZE;
            glm::vec3 p = glm::vec3(pX, chunkNE->getTile(x, 0)->y, pZ);
            // Check for LOD boundaries on edge vertices .. as p.y may need to be modified to prevent seams in LOD levels
            if (x != 0 && x < constants::CHUNK_SIZE
                && chunkNE->levelOfDetail > levelOfDetail) {
                /* if
                 * -- we are on the x boundary (excluding corners)
                 * -- and we are not on the edge of the map
                 * -- and the level of detail decreases
                 *
                 * then we must seam the tear by making every second emitted vertex (vertex without equivalent vertex
                 * in neighbouring chunk) along the boundary's height equal to the average of it's emitted neighbours */
                if ((x - levelOfDetail) % (levelOfDetail * 2) == 0)
                    if (x + levelOfDetail < constants::CHUNK_SIZE) {
                        double avg = (chunkNE->getTile(x - levelOfDetail, 0)->y + chunkNE->getTile(x + levelOfDetail, 0)->y) / 2.0f;
                        p.y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
//                    p.y = 0;
                    }
            }
            mesh->vertices.push_back(p);
            mesh->normals.push_back(getPointNormal(x, constants::CHUNK_SIZE));

            if (x != 0) {
                // Generate triangle elements using indices of E, S & W points
                unsigned int iWest = (x / levelOfDetail + 1) * (constants::CHUNK_SIZE / levelOfDetail) - 1;
                unsigned int iSouth = iWest - constants::CHUNK_SIZE / levelOfDetail;
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
    // Lastly create the Northern most point using the final verts from NW, NE and N chunks
    // (if both NW & NE chunks are loaded)
    Chunk* chunkN = world->tryGetChunk(posX + 1, posZ + 1);
    if (chunkNW != NULL && chunkNE != NULL && chunkN != NULL) {
        float pX = cX + constants::CHUNK_SIZE;
        float pZ = cZ + constants::CHUNK_SIZE;
        glm::vec3 p = glm::vec3(pX, chunkN->getTile(0, 0)->y, pZ);

        if (chunkNW->levelOfDetail > levelOfDetail) {
            double avg = (chunkNW->getTile(0, constants::CHUNK_SIZE - 2 * levelOfDetail)->y + chunkN->getTile(0, 0)->y) / 2.0f;
            mesh->vertices[iLastNW].y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
        }
        if (chunkNE->levelOfDetail > levelOfDetail) {
            double avg = (chunkNE->getTile(constants::CHUNK_SIZE - 2 * levelOfDetail, 0)->y + chunkN->getTile(0, 0)->y) / 2.0f;
            mesh->vertices[iLastNE].y = static_cast<float>(avg + LOD_SEEM_HEIGHT);
        }

        mesh->vertices.push_back(p);
        mesh->normals.push_back(getPointNormal(constants::CHUNK_SIZE, constants::CHUNK_SIZE));

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

    regenerateMesh = false;
}


glm::vec3 Chunk::getPointNormal(int x, int z) {
    float pX = posX * constants::CHUNK_SIZE + x;
    float pZ = posZ * constants::CHUNK_SIZE + z;
    float yPX = world->noiseGenerator->GetSimplexFractal(pX + 1, pZ);
    float yNX = world->noiseGenerator->GetSimplexFractal(pX - 1, pZ);
    float yPZ = world->noiseGenerator->GetSimplexFractal(pX, pZ + 1);
    float yNZ = world->noiseGenerator->GetSimplexFractal(pX, pZ - 1);
    return glm::normalize(glm::vec3(yPX - yNX, 2.0, yPZ - yNZ));
}