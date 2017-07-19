//
// Created by montgomery anderson on 6/07/17.
//

#include <core/TextRenderer.h>
#include <core/Constants.h>
#include "GameState.h"


GameState::GameState(Engine *engine) : State(engine) {}


GameState::~GameState() {}


int GameState::initialise() {
    timer = Timer::Start();

    // Initialise the world
    // TODO generation phase
    world = new World(constants::WORLD_DEPTH, constants::WORLD_WIDTH);

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
    world->Render();
}