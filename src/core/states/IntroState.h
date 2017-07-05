//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_INTROSTATE_H
#define RECLAIMER_INTROSTATE_H

#include "State.h"

class IntroState : public State {
public:
    const std::string INTRO_TEXT = "Reclaimer 0.1";

    IntroState(Engine *engine);
    ~IntroState();

    int initialise();
    void cleanup();

    void pause();
    void resume();

    void handleEvents();
    void update();
    void drawText();
    void drawGl();
protected:
    std::string name = "IntroState";
private:
};


#endif //RECLAIMER_INTROSTATE_H
