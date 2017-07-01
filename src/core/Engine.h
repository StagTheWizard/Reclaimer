//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_ENGINE_H
#define RECLAIMER_ENGINE_H


class State;
class EngineRenderer;


#include <vector>
#include <SFML/Window.hpp>

#include "Camera.h"


class Engine {
public:
    Engine();
    ~Engine();

    bool isRunning() { return running; }


    int initialise();
    void cleanup();
    int start();

    void changeState(State *state);
    void pushState(State *state);
    void popState();

    void handleEvents();
    void update();
    void draw();
    int quit();
private:
    sf::Window *window;
    Camera *camera;
    EngineRenderer *renderer;

    std::vector<State *> states;

    bool running;
};


#endif //RECLAIMER_ENGINE_H