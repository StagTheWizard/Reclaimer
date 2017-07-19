//
// Created by montgomery anderson on 30/06/17.
//

#include "Engine.h"

#include "states/State.h"
#include "TextRenderer.h"
#include "Constants.h"


Engine::Engine() {
    this->textRenderer = new TextRenderer(this);
}


Engine::~Engine() {}


int Engine::initialise() {
    // initialise the context
    int glfwResult = glfwInit();
    if (!glfwResult) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, constants::WINDOW_TITLE.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // activate the window
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // swap every screen update
    glfwSwapInterval(1);

    // load resources
    textRenderer->initialise();
    // initialise OpenGL states

    return EXIT_SUCCESS;
}


void Engine::cleanup() {}


int Engine::start() {
    running = true;

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.3f, 0.3f, 0.35f, 1);

    while (!glfwWindowShouldClose(window)) {
        // handle events
        // TODO adjust viewport on resive event

        // update
        this->update();

        // draw
        this->draw();
    }

    running = false;

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
    glfwPollEvents();
    if (states.size() < 1) return;
    State* currentState = states[states.size() - 1];
    // push OpenGL state
    // clear the buffers
    glViewport(0, 0, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render OpenGL
    currentState->drawGl();
    currentState->drawText();

    // end the current frame (internally swaps the buffers)
    glfwSwapBuffers(window);
}


int Engine::quit() {
    // release resources
    glfwDestroyWindow(window);
    glfwTerminate();

    // and exit
    return EXIT_SUCCESS;
}