//
// Created by montgomery anderson on 30/06/17.
//

#include <iostream>
#include <sstream>
#include "IntroState.h"

#include "core/TextRenderer.h"
#include "GameState.h"


IntroState::IntroState(Engine *engine) : State(engine) {}


IntroState::~IntroState() {}


int IntroState::initialise() {
    timer = Timer::Start();
    return EXIT_SUCCESS;
}


void IntroState::cleanup() {}


void IntroState::pause() {}


void IntroState::resume() {}


void IntroState::handleEvents() {}


void IntroState::update() {
    // After the intro duraction has passed, move onto the game state
    if (timer.seconds() >= IntroState::INTRO_DURATION)
        engine->pushState(new GameState(engine));
    this->runTime = timer.str();
}


void IntroState::drawText() {
    engine->textRenderer->render(INTRO_TEXT, Font::DEFAULT, 14, glm::vec2(20, 20));
    engine->textRenderer->render(this->name, Font::DEFAULT, 14, glm::vec2(20, 40));
    engine->textRenderer->render(this->runTime, Font::DEFAULT, 14, glm::vec2(20, 60));
}


void IntroState::drawGl() {

}