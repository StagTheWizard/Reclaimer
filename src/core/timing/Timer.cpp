//
// Created by montgomery anderson on 18/07/17.
//

#include "Timer.h"

#include <cmath>


Timer Timer::Start() {
    return Timer();
}


Timer::~Timer() {}


Timer::Timer() {
    startTime = std::clock();
}


float Timer::duration() {
    return (std::clock() - startTime) / CLOCKS_PER_SEC;
}


long Timer::days() {
    return (long) floor(hours() / 24);
}


long Timer::hours() {
    return (long) floor(minutes() / 60);
}


long Timer::minutes() {
    return (long) floor(duration() / 60);
}


long Timer::seconds() {
    return (long) duration();
}


long Timer::milliseconds() {
    return (long) (duration() / 1000);
}


