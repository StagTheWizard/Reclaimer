//
// Created by montgomery anderson on 19/07/17.
//

#include "WorldRenderer.h"

#include <cstdlib>
#include <glm/vec3.hpp>
#include <core/world/TerrainMesh.h>


WorldRenderer::WorldRenderer(Engine *engine) {
    this->engine = engine;
}


WorldRenderer::~WorldRenderer() {

}


int WorldRenderer::initialise() {
    initialiseShaders();

    return EXIT_SUCCESS;
}


int WorldRenderer::initialiseShaders() {
    terrainShader = new TerrainShaderProgram();
    terrainShader->initialise();

    return EXIT_SUCCESS;
}


void WorldRenderer::renderTerrain(TerrainMesh *mesh) {
    terrainShader->activate();
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    glm::mat4 mvMatrix = viewMatrix * modelMatrix;
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(mvMatrix));
    terrainShader->updateUniforms(modelMatrix, viewMatrix, mvMatrix, mvpMatrix, normalMatrix, cameraPosition, sun.position);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &elementBuffer);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // First VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->normals.size(), &mesh->normals[0], GL_STATIC_DRAW);
//
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec3) * mesh->elements.size(), &mesh->elements[0], GL_STATIC_DRAW);


    glBindVertexArray(vao);
//    glPatchParameteri(GL_PATCH_VERTICES, 3);
//    glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
//    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, mesh->elements.size(), GL_UNSIGNED_INT, NULL);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &elementBuffer);
    glDeleteVertexArrays(1, &vao);
}
