#include <iostream>

#include "core/Constants.h"
#include "core/states/Introstate.h"
#include "core/Engine.h"


int main(int argc, char **argv) {
    std::cout << "Launching " << constants::WINDOW_TITLE << std::endl;

    Engine *engine = new Engine();
    if (engine->initialise()) {
        std::cout << "Engine failed to initialise, closing now." << std::endl;
        return EXIT_FAILURE;
    }

    engine->pushState(new IntroState(engine));
    int exitCode = engine->start();

    return exitCode;
}