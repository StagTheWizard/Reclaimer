//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_ENGINERENDERER_H
#define RECLAIMER_ENGINERENDERER_H


#include <glm/vec2.hpp>

#include "TextRenderModule.h"


class EngineRenderer {
public:
    EngineRenderer();
    ~EngineRenderer();

    int initialise();

    void renderText(std::string text, Font font, int fontSize, glm::vec2 screenPos);
protected:
    TextRenderModule *textRenderModule;
private:
};


#endif //RECLAIMER_ENGINERENDERER_H
