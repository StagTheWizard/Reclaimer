//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_ENGINE_H
#define RECLAIMER_ENGINE_H


class State;
class TextRenderer;


#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/rendering/WorldRenderer.h>

#include "Camera.h"
#include "Constants.h"


class Engine {
public:
    static Engine* Instance();

    GLFWwindow *window;
    float windowHeight = constants::WINDOW_HEIGHT;
    float windowWidth = constants::WINDOW_WIDTH;
    float aspectRatio() {
        return windowWidth / windowHeight;
    }

    TextRenderer *textRenderer = NULL;
    WorldRenderer *worldRenderer = NULL;

    bool isRunning() { return running; }


    int initialise();
    void cleanup();
    int start();

    void changeState(State *state);
    void pushState(State *state);
    void popState();
    State* peekState();

    void handleEvents();
    void update();
    void draw();

    int stop();
    int quit();
private:
    static Engine* instance;

    Engine();
    ~Engine();
    Camera *camera = NULL;


    std::vector<State *> states;

    bool running;
};


#endif //RECLAIMER_ENGINE_H