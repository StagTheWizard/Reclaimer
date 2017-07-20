//
// Created by montgomery anderson on 6/07/17.
//

#ifndef RECLAIMER_GAMESTATE_H
#define RECLAIMER_GAMESTATE_H


#include "State.h"

#include <string>
#include <core/timing/Timer.h>
#include <core/world/World.h>


class Engine;


class GameState : public State {
public:
    GameState(Engine *engine);
    ~GameState();

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
    std::string name = "GameState";
    std::string runTime;
    std::string cameraInfo;
    std::string meshInfo;
private:
    Timer timer;
    World *world;
    Camera *camera;
};


#endif //RECLAIMER_GAMESTATE_H
