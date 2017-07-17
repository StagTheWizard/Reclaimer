//
// Created by montgomery anderson on 6/07/17.
//

#ifndef RECLAIMER_GAMESTATE_H
#define RECLAIMER_GAMESTATE_H


#include "State.h"

#include <string>
#include <core/timing/Timer.h>


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
    void update();
    void drawText();
    void drawGl();
protected:
    std::string name = "GameState";
    std::string runTime;
private:
    Timer timer;
};


#endif //RECLAIMER_GAMESTATE_H
