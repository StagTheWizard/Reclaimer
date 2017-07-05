//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_ENGINE_H
#define RECLAIMER_ENGINE_H


class State;
class TextRenderer;


#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Camera.h"


class Engine {
public:
    sf::RenderWindow *window;

    TextRenderer *textRenderer;

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
    Camera *camera;

    std::vector<State *> states;

    bool running;
};


#endif //RECLAIMER_ENGINE_H