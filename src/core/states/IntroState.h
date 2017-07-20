//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_INTROSTATE_H
#define RECLAIMER_INTROSTATE_H

#include "State.h"

#include "core/timing/Timer.h"

class IntroState : public State {
public:
    const std::string INTRO_TEXT = "Reclaimer 0.1";
    const int INTRO_DURATION = 2;

    IntroState(Engine *engine);
    ~IntroState();

    int initialise();
    void cleanup();

    void pause();
    void resume();

    void handleEvents();
//    void keyPressed(GLFWwindow* window, int key, int scanCode, int action, int mods);
    void cursorMoved(GLFWwindow* window, double xPos, double yPos);
    void processInput();

    void update();
    void draw();
protected:
    std::string name = "IntroState";
    std::string runTime;
private:
    Timer timer;
};


#endif //RECLAIMER_INTROSTATE_H
