//
// Created by montgomery anderson on 19/07/17.
//

#ifndef RECLAIMER_WORLDRENDERER_H
#define RECLAIMER_WORLDRENDERER_H


#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "core/structs/Light.h"
#include "core/rendering/shaders/TerrainShaderProgram.h"


class Engine;
class TerrainMesh;


class WorldRenderer {
public:
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec4 cameraPosition;

    // NOTE: W = 0, (meaning infinitely far away in a homogeneous system)
    Light sun = Light {
            glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            0.0f,
            0.005f
    };
//    glm::vec4 sunPosition = glm::vec4(1.0f, 2.0f, 1.0f, 0.0f);

    WorldRenderer(Engine* engine);
    ~WorldRenderer();

    int initialise();
    void renderTerrain(TerrainMesh *mesh);
protected:
private:
    Engine *engine;
    TerrainShaderProgram *terrainShader;

    GLuint vao;
    GLuint vertexBuffer;
    GLuint normalBuffer;
    GLuint elementBuffer;

    int initialiseShaders();
};


#endif //RECLAIMER_WORLDRENDERER_H
