//
// Created by montgomery anderson on 30/06/17.
//

#include <iostream>
#include "Engine.h"

#include "states/State.h"
#include "core/rendering/TextRenderer.h"
#include "Constants.h"


/*void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    Engine::Instance()->peekState()->keyPressed(
            window, key, scanCode, action, mods
    );
}*/


void cursorCallback(GLFWwindow* window, double xPos, double yPos) {
    State *state = Engine::Instance()->peekState();
    if (state != NULL)
        state->cursorMoved(window, xPos, yPos);
}


Engine* Engine::instance = NULL;


Engine* Engine::Instance() {
    if (Engine::instance == NULL)
        Engine::instance = new Engine();
    return Engine::instance;
}


Engine::Engine() {
    this->textRenderer = new TextRenderer(this);
    this->worldRenderer = new WorldRenderer(this);
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

    // bind callbacks
//    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorCallback);

    // swap every screen update
    glfwSwapInterval(1);

    // load resources
    textRenderer->initialise();
    worldRenderer->initialise();

    return EXIT_SUCCESS;
}


void Engine::cleanup() {}


int Engine::start() {
    running = true;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window) && running) {
        // handle events
        glfwPollEvents();

        // TODO adjust viewport on resive event

        // update
        this->update();

        // draw
        this->draw();
    }

    // exit
    return this->quit();
}


int Engine::stop() {
    running = false;
    return EXIT_SUCCESS;
}


void Engine::changeState(State *state) {}


void Engine::pushState(State *state) {
    states.push_back(state);
}


void Engine::popState() {
    states.pop_back();
}


State *Engine::peekState() {
    if (states.size() < 1)
        return NULL;
    return states[states.size() - 1];
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
    glClearColor(0.65f, 0.65f, 0.75f, 1);

    glViewport(0, 0, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // render OpenGL
    currentState->draw();

    // end the current frame (internally swaps the buffers)
    glfwSwapBuffers(window);
}


int Engine::quit() {
    running = false;
    // release resources
    glfwDestroyWindow(window);
    glfwTerminate();

    // and exit
    return EXIT_SUCCESS;
}
