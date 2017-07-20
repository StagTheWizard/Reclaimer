//
// Created by montgomery anderson on 30/06/17.
//

#include <iostream>
#include <sstream>
#include "IntroState.h"

#include "core/rendering/TextRenderer.h"
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


void IntroState::processInput() {
    if (glfwGetKey(engine->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        engine->stop();
}


void IntroState::cursorMoved(GLFWwindow *window, double xPos, double yPos) {

}


void IntroState::update() {
    this->processInput();

    // After the intro duraction has passed, move onto the game state
    if (timer.seconds() >= IntroState::INTRO_DURATION) {
        GameState *gameState = new GameState(engine);
        gameState->initialise();
        engine->pushState(gameState);
    }
    this->runTime = timer.str();
}


void IntroState::draw() {
    engine->textRenderer->render(INTRO_TEXT, Font::DEFAULT, 14, glm::vec2(20, 20));
    engine->textRenderer->render(this->name, Font::DEFAULT, 14, glm::vec2(20, 40));
    engine->textRenderer->render(this->runTime, Font::DEFAULT, 14, glm::vec2(20, 60));
}
