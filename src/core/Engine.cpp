//
// Created by montgomery anderson on 30/06/17.
//

#include "Engine.h"

#include <SFML/OpenGL.hpp>


Engine::Engine() {}


Engine::~Engine() {}


int Engine::initialise() {
    // create the window
    window = new sf::Window(sf::VideoMode(800, 600), "Reclaimer", sf::Style::Default, sf::ContextSettings(32));
    window->setVerticalSyncEnabled(true);

    // activate the window
    window->setActive(true);

    // load resources
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

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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


void Engine::pushState(State *state) {}


void Engine::popState() {}


void Engine::handleEvents() {}


void Engine::update() {}


void Engine::draw() {}


int Engine::quit() {
    // release resources

    // and exit
    return EXIT_SUCCESS;
}