//
// Created by montgomery anderson on 30/06/17.
//

#include "TextRenderer.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "core/text/FontChar.h"
#include "core/text/FontTextureAtlas.h"
#include "Engine.h"
#include "Constants.h"


TextRenderer::TextRenderer(Engine *engine) {
    this->engine = engine;
}


TextRenderer::~TextRenderer() {}


int TextRenderer::initialise() {
    initialiseShaders();

    return EXIT_SUCCESS;
}


int TextRenderer::initialiseShaders() {
    textShader = new TextShaderProgram();
    textShader->initialise();
    textShader->bindUniforms();

    return EXIT_SUCCESS;
}


int TextRenderer::initialiseFonts() {
    return EXIT_SUCCESS;
}


void TextRenderer::render(std::string textStr, Font fontEnum, int size, glm::vec2 pos) {
    render(textStr, fontEnum, size, pos, glm::vec4(1.0, 0.6, 0.0, 1.0));
}


void TextRenderer::render(std::string textStr, Font fontEnum, int size, glm::vec2 pos, glm::vec3 color) {
    render(textStr, fontEnum, size, pos, glm::vec4(color, 1.0));
}


void TextRenderer::render(std::string textStr, Font fontEnum, int size,
                          glm::vec2 pos, glm::vec4 color) {

    // Initialise freetype
    FT_Library library;
    if (FT_Init_FreeType(&library))
        throw std::runtime_error("FT_Init_FreeType failed");

    FT_Face face;
    if (FT_New_Face(library, menloPath.c_str(), 0, &face))
        throw std::runtime_error("FT_New_Face failed");

    FT_Set_Pixel_Sizes(face, 0, 48);

    glGenTextures(1, &textShader->uniformTextureMap);
    glBindTexture(GL_TEXTURE_2D, textShader->uniformTextureMap);
    glActiveTexture(GL_TEXTURE0);
    menloAtlas_12pt = new FontTextureAtlas(face, size);

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    std::string line = "";
    std::vector<std::string> lines;
    std::string::iterator itr;
    for (itr = textStr.begin(); itr < textStr.end(); itr++) {
        if (*itr == '\n') {
            lines.push_back(line);
            line = "";
        } else {
            line += *itr;
        }
    }
    if (line != "") lines.push_back(line);

    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;

    int yAdvance = 0;
    // foreach line
    for (unsigned int i = 0; i < lines.size(); i++) {
        line = lines[i];
        unsigned int j = 0;
        float xAdvance = 0;
        // foreach character in the line
        for (itr = line.begin(); itr < line.end(); itr++, j++) {
            char ch = *itr;
            FontChar *fchar = &menloAtlas_12pt->characters[ch];

            glm::vec2 vertex_top_left       = glm::vec2(pos.x + xAdvance,
                                                        pos.y - yAdvance + size);

            glm::vec2 vertex_top_right      = glm::vec2(pos.x + xAdvance + fchar->bitmapWidth,
                                                        pos.y - yAdvance + size);

            glm::vec2 vertex_bottom_right   = glm::vec2(pos.x + xAdvance + fchar->bitmapWidth,
                                                        pos.y - yAdvance + size + fchar->height);

            glm::vec2 vertex_bottom_left    = glm::vec2(pos.x + xAdvance,
                                                        pos.y - yAdvance + size + fchar->height);

            if (ch == ' ')
                xAdvance += fchar->advanceX;
            else
                xAdvance += fchar->bitmapWidth + 1;

            vertices.push_back(vertex_top_right);
            vertices.push_back(vertex_bottom_left);
            vertices.push_back(vertex_top_left);

            vertices.push_back(vertex_bottom_left);
            vertices.push_back(vertex_top_right);
            vertices.push_back(vertex_bottom_right);

            /*vertices.push_back(vertex_top_left);
            vertices.push_back(vertex_bottom_left);
            vertices.push_back(vertex_bottom_right);
            vertices.push_back(vertex_top_right);*/

            glm::vec2 UV_bottom_left = glm::vec2(
                    fchar->uvOffsetX,
                    fchar->uvOffsetY);
            glm::vec2 UV_bottom_right = glm::vec2(
                    fchar->uvOffsetX + fchar->bitmapWidth / menloAtlas_12pt->width,
                    fchar->uvOffsetY);
            glm::vec2 UV_top_right = glm::vec2(
                    fchar->uvOffsetX + fchar->bitmapWidth / menloAtlas_12pt->width,
                    fchar->uvOffsetY + fchar->bitmapHeight / menloAtlas_12pt->height);
            glm::vec2 UV_top_left = glm::vec2(
                    fchar->uvOffsetX,
                    fchar->uvOffsetY + fchar->bitmapHeight / menloAtlas_12pt->height);

            UVs.push_back(UV_top_right);
            UVs.push_back(UV_bottom_left);
            UVs.push_back(UV_top_left);

            UVs.push_back(UV_bottom_left);
            UVs.push_back(UV_top_right);
            UVs.push_back(UV_bottom_right);

            /*UVs.push_back(UV_top_left);
            UVs.push_back(UV_bottom_left);
            UVs.push_back(UV_bottom_right);
            UVs.push_back(UV_top_right);*/
        }
        // Move to the next line
        yAdvance += size;
    }

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glm::vec2 testVerts[4] = {
//            glm::vec2(10.0, 20.0),
//            glm::vec2(10.0, 10.0),
//            glm::vec2(20.0, 10.0),
//            glm::vec2(20.0, 20.0),
//            glm::vec2(10.0, 20.0),
//            glm::vec2(10.0, 10.0),
//            glm::vec2(20.0, 10.0),
//            glm::vec2(20.0, 20.0),
//    };

//    glm::vec2 testUVs[4] = {
//            glm::vec2(0.510057449, 0.692307711),
//            glm::vec2(0.510057449, 0.0),
//            glm::vec2(0.521551728, 0.0),
//            glm::vec2(0.521551728, 0.692307711)
//    };


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &uvBuffer);

    textShader->activate();
    textShader->updateUniforms(glm::vec3(color));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 1st attribute buffer, vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(testVerts), testVerts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    // 2nd attribute buffer, UVs
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * UVs.size(), &UVs[0], GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(testUVs), testUVs, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    std::cout << "v.size " << vertices.size() << " uv.size " << UVs.size() << std::endl;
//    glDisable(GL_BLEND);

    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteVertexArrays(1, &vao);

    delete menloAtlas_12pt;
}