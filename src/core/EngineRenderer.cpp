//
// Created by montgomery anderson on 30/06/17.
//

#include "EngineRenderer.h"


EngineRenderer::EngineRenderer() {
    textRenderModule = new TextRenderModule();
}


EngineRenderer::~EngineRenderer() {
    delete textRenderModule;
}


int EngineRenderer::initialise() {
    // initialise render modules
    if (textRenderModule->initialise()) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}


void EngineRenderer::renderText(std::string text, Font font, int fontSize, glm::vec2 screenPos) {
    textRenderModule->print(text, font, fontSize, screenPos);
}