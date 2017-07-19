//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_TEXTRENDERMODULE_H
#define RECLAIMER_TEXTRENDERMODULE_H


#include <string>
#include <map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include "shaders/TextShaderProgram.h"


class Engine;
class FontTextureAtlas;


enum Font {
    DEFAULT,
    MENLO
};


/**
 * The TextRenderModule is simply a module of the EngineRenderer responsible for all
 * rendering code relevant to text rendering.
 */
class TextRenderer {
public:
    TextRenderer(Engine* engine);
    ~TextRenderer();

    int initialise();
    void render(std::string textStr, Font fontEnum, int size, glm::vec2 pos);
    void render(std::string textStr, Font fontEnum, int size, glm::vec2 pos, glm::vec3 color);
    void render(std::string textStr, Font fontEnum, int size, glm::vec2 pos, glm::vec4 color);
protected:
private:
    Engine* engine;
    TextShaderProgram *textShader;

    GLuint vao;
    GLuint vertexBuffer;
    GLuint uvBuffer;

    FontTextureAtlas* menloAtlas_12pt;

    int initialiseShaders();
    int initialiseFonts();

    std::string menloPath = "assets/fonts/Menlo-Regular.ttf";
};

#endif //RECLAIMER_TEXTRENDERMODULE_H
