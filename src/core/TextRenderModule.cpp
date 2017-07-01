//
// Created by montgomery anderson on 30/06/17.
//

#include "TextRenderModule.h"
#include <cstdlib>
#include <vector>
#include <glm/vec2.hpp>
#include <iostream>


TextRenderModule::TextRenderModule() {}


TextRenderModule::~TextRenderModule() {}


int TextRenderModule::initialise() {
    initialiseShaders();
    initialiseFonts();

    return EXIT_SUCCESS;
}


int TextRenderModule::initialiseShaders() {
    textShader = new TextShaderProgram();
    textShader->initialise();
    textShader->bindUniforms();

    return EXIT_SUCCESS;
}


int TextRenderModule::initialiseFonts() {
    initialiseFont(MENLO);
    return EXIT_SUCCESS;
}


int TextRenderModule::initialiseFont(Font font) {

    return EXIT_SUCCESS;
}


void TextRenderModule::print(std::string text, Font font, int size, glm::vec2 pos) {
    /*std::string line = "";
    std::vector<std::string> lines;
    std::string::iterator itr;
    for (itr = text.begin(); itr < text.end(); itr++) {
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
    for (unsigned int i = 0; i < lines.size(); i++) {
        line = lines[i];
        unsigned int j = 0;
        float xAdvance = 0;
        for (itr = line.begin(); itr < line.end(); itr++, j++) {
            char ch = *itr;
            FontChar &fchar = menloAtlas_12pt->characters[ch];

            glm::vec2 vertex_top_left = glm::vec2(x + xAdvance, y - yAdvance + size - fchar.height);
            glm::vec2 vertex_top_right = glm::vec2(x + xAdvance + fchar.advanceX, y - yAdvance + size - fchar.height);
            glm::vec2 vertex_bottom_right = glm::vec2(x + xAdvance + fchar.advanceX, y - yAdvance + size);
            glm::vec2 vertex_bottom_left = glm::vec2(x + xAdvance, y - yAdvance + size);
            xAdvance += fchar.advanceX;

            vertices.push_back(vertex_top_right);
            vertices.push_back(vertex_bottom_left);
            vertices.push_back(vertex_top_left);

            vertices.push_back(vertex_bottom_left);
            vertices.push_back(vertex_top_right);
            vertices.push_back(vertex_bottom_right);

            glm::vec2 UV_bottom_left = glm::vec2(
                    fchar.uvOffsetX,
                    fchar.uvOffsetY);
            glm::vec2 UV_bottom_right = glm::vec2(
                    fchar.uvOffsetX + fchar.bitmapWidth / menloAtlas_12pt->width,
                    fchar.uvOffsetY);
            glm::vec2 UV_top_right = glm::vec2(
                    fchar.uvOffsetX + fchar.bitmapWidth / menloAtlas_12pt->width,
                    fchar.uvOffsetY + fchar.bitmapHeight / menloAtlas_12pt->height);
            glm::vec2 UV_top_left = glm::vec2(
                    fchar.uvOffsetX,
                    fchar.uvOffsetY + fchar.bitmapHeight / menloAtlas_12pt->height);

            UVs.push_back(UV_top_right);
            UVs.push_back(UV_bottom_left);
            UVs.push_back(UV_top_left);

            UVs.push_back(UV_bottom_left);
            UVs.push_back(UV_top_right);
            UVs.push_back(UV_bottom_right);
        }
        yAdvance += size;
    }


    textShader->activate();
    glUniform1i(textShader->uniformTextureMap, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, menloAtlas_12pt->uniformTextureLocation);
    glUniform1i(menloAtlas_12pt->uniformTextureLocation, 0);

    // 1st attribute buffer, vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);


    // 2nd attribute buffer, UVs
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    std::cout << "v.size " << vertices.size() << " uv.size " << UVs.size() << std::endl;
    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);*/
}