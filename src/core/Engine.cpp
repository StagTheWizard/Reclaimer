//
// Created by montgomery anderson on 30/06/17.
//

#include "Engine.h"

#include <SFML/OpenGL.hpp>

#include "states/State.h"
#include "TextRenderer.h"


Engine::Engine() {
    this->textRenderer = new TextRenderer(this);
}


Engine::~Engine() {}


int Engine::initialise() {
    // create the window
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Reclaimer", sf::Style::Default, sf::ContextSettings(32));
    window->setVerticalSyncEnabled(true);

    // activate the window
    window->setActive(true);

    // load resources
    textRenderer->initialise();
    // initialise OpenGL states

    return EXIT_SUCCESS;
}


void Engine::cleanup() {}


int Engine::start() {
    running = true;
    while (running) {
        // handle events
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // kill the engine
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // update
        this->update();

        // draw
        this->draw();

        // end the current frame (internally swaps the buffers)
        window->display();
    }

    // exit
    return this->quit();
}


void Engine::changeState(State *state) {}


void Engine::pushState(State *state) {
    states.push_back(state);
}


void Engine::popState() {
    states.pop_back();
}


void Engine::handleEvents() {}


void Engine::update() {
    if (states.size() < 1) return;
    State* currentState = states[states.size() - 1];
    currentState->update();
}


void Engine::draw() {
    if (states.size() < 1) return;
    State* currentState = states[states.size() - 1];
    // push OpenGL state
    // clear the buffers
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render OpenGL
    //glDraw..

    window->clear(sf::Color::Black);
//    window->pushGLStates();
    // render SFML
    currentState->drawText();
    // pop SFML state
//    window->popGLStates();
}


int Engine::quit() {
    // release resources

    // and exit
    return EXIT_SUCCESS;
}