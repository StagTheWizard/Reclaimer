//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TERRAINMESH_H
#define RECLAIMER_TERRAINMESH_H


#include <vector>
#include <glm/vec3.hpp>


struct TerrainMesh {
    std::vector<glm::vec3> verticies;
    std::vector<glm::vec2> edges;


    void append(TerrainMesh *other) {
        this->verticies.reserve(this->verticies.size() + other->verticies.size());
        this->verticies.insert(this->verticies.end(), other->verticies.begin(), other->verticies.end());
    }
};


#endif //RECLAIMER_TERRAINMESH_H
