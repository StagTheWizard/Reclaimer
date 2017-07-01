//
// Created by montgomery anderson on 30/06/17.
//

#include "IntroState.h"
#include "core/EngineRenderer.h"


IntroState::IntroState(Engine *engine) : State(engine) {}


IntroState::~IntroState() {}


int IntroState::initialise() {
    return EXIT_SUCCESS;
}


void IntroState::cleanup() {}


void IntroState::pause() {}


void IntroState::resume() {}


void IntroState::handleEvents() {}


void IntroState::update() {}


void IntroState::draw(EngineRenderer *renderer) {
    renderer->renderText(INTRO_TEXT, Font::DEFAULT, 16, glm::vec2(20, 20));
}