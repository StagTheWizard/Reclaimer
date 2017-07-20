//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_STATE_H
#define RECLAIMER_STATE_H


#include <string>

#include "core/Engine.h"


class State {
public:
    virtual int initialise() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents() = 0;
//    virtual void keyPressed(GLFWwindow* window, int key, int scanCode, int action, int mods) = 0;
//    virtual void cursorMoved(GLFWwindow* window, int xPos, int yPos) = 0;

    virtual void update() = 0;
    virtual void draw() = 0;


    void ChangeState(Engine *engine, State *state) {
        engine->changeState(state);
    }
protected:
    std::string name;


    State(Engine *engine) {
        this->engine = engine;
    }


    ~State() {};
    Engine *engine;
};


#endif //RECLAIMER_STATE_H