//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_TEXTRENDERMODULE_H
#define RECLAIMER_TEXTRENDERMODULE_H


#include <string>
#include <map>
#include <SFML/OpenGL.hpp>

#include "shaders/TextShaderProgram.h"


enum Font {
    DEFAULT,
    MENLO
};


/**
 * The TextRenderModule is simply a module of the EngineRenderer responsible for all
 * rendering code relevant to text rendering.
 */
class TextRenderModule {
public:
    TextRenderModule();
    ~TextRenderModule();

    int initialise();
    void print(std::string text, Font font, int size, glm::vec2 pos);
protected:
private:
    TextShaderProgram *textShader;

    GLuint vao;
    GLuint vertexBuffer;
    GLuint uvBuffer;

    std::map<Font, std::string> fontPathMap = {
            { Font::DEFAULT, "assets/fonts/Menlo-Regular.ttf"},
            { Font::MENLO, "assets/fonts/Menlo-Regular.ttf"},
    };

    int initialiseShaders();
    int initialiseFonts();
    int initialiseFont(Font font);
};

#endif //RECLAIMER_TEXTRENDERMODULE_H
