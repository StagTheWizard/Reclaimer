//
// Created by montgomery anderson on 6/07/17.
//

#include <core/TextRenderer.h>
#include "GameState.h"


GameState::GameState(Engine *engine) : State(engine) {}


GameState::~GameState() {}


int GameState::initialise() {
    timer = Timer::Start();
    return EXIT_SUCCESS;
}


void GameState::cleanup() {}


void GameState::pause() {}


void GameState::resume() {}


void GameState::handleEvents() {}


void GameState::update() {
    this->runTime = timer.str();
}


void GameState::drawText() {
    engine->textRenderer->render(this->name, Font::DEFAULT, 14, glm::vec2(20, 40));
    engine->textRenderer->render(this->runTime, Font::DEFAULT, 14, glm::vec2(20, 60));
}


void GameState::drawGl() {

}