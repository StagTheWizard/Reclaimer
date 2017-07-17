//
// Created by montgomery anderson on 6/07/17.
//

#ifndef RECLAIMER_GAMESTATE_H
#define RECLAIMER_GAMESTATE_H


#include "State.h"

#include <string>


class Engine;


class GameState : State {
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
private:
};


#endif //RECLAIMER_GAMESTATE_H
