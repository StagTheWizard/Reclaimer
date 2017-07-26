//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TERRAINMESH_H
#define RECLAIMER_TERRAINMESH_H


#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glad/glad.h>


struct TerrainMesh {
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> elements;
    std::vector<glm::vec3> normals;

    void append(TerrainMesh *other) {
        this->vertices.reserve(this->vertices.size() + other->vertices.size());
        this->vertices.insert(this->vertices.end(), other->vertices.begin(), other->vertices.end());
        this->elements.reserve(this->elements.size() + other->elements.size());
        this->elements.insert(this->elements.end(), other->elements.begin(), other->elements.end());
        this->normals.reserve(this->normals.size() + other->normals.size());
        this->normals.insert(this->normals.end(), other->normals.begin(), other->normals.end());
    }
};


#endif //RECLAIMER_TERRAINMESH_H
