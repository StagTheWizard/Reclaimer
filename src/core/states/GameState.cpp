//
// Created by montgomery anderson on 6/07/17.
//

#include <core/TextRenderer.h>
#include "GameState.h"


GameState::GameState(Engine *engine) : State(engine) {}


GameState::~GameState() {}


int GameState::initialise() {
    return EXIT_SUCCESS;
}


void GameState::cleanup() {}


void GameState::pause() {}


void GameState::resume() {}


void GameState::handleEvents() {}


void GameState::update() {}


void GameState::drawText() {
    engine->textRenderer->render(this->name, Font::DEFAULT, 14, glm::vec2(20, 40));
}


void GameState::drawGl() {

}