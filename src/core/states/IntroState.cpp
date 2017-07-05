//
// Created by montgomery anderson on 30/06/17.
//

#include "IntroState.h"

#include "core/TextRenderer.h"


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


void IntroState::drawText() {
    engine->textRenderer->render(INTRO_TEXT, Font::DEFAULT, 18, glm::vec2(20, 20));
    engine->textRenderer->render(this->name, Font::DEFAULT, 14, glm::vec2(20, 40));
}


void IntroState::drawGl() {

}