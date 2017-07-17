//
// Created by montgomery anderson on 18/07/17.
//

#include "Timer.h"

#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;
using namespace std::chrono;

Timer Timer::Start() {
    return Timer();
}


Timer::~Timer() {}


Timer::Timer() {
    startTime = high_resolution_clock::now();
}


long Timer::days() {
    return (long) floor(hours() / 24);
}


long Timer::hours() {
    high_resolution_clock::time_point now = high_resolution_clock::now();
    return duration_cast<chrono::hours>(now - startTime).count();
}


long Timer::minutes() {
    high_resolution_clock::time_point now = high_resolution_clock::now();
    return duration_cast<chrono::minutes>(now - startTime).count();
}


long Timer::seconds() {
    high_resolution_clock::time_point now = high_resolution_clock::now();
    return duration_cast<chrono::seconds>(now - startTime).count();
}


long Timer::milliseconds() {
    high_resolution_clock::time_point now = high_resolution_clock::now();
    return duration_cast<chrono::milliseconds>(now - startTime).count();
}


std::string Timer::str() {
    std::ostringstream strStream;
    // days render as is
    strStream << this->days() << ":";
    // hours render 00
    if (this->hours() < 10)
        strStream << 0;
    strStream << this->hours() % 24 << ":";
    // minutes render 00
    long m = this->minutes();
    if (m < 10)
        strStream << 0;
    strStream << m % 60 << ":";
    // seconds render 00
    long s = this->seconds();
    if (s < 10)
        strStream << 0;
    strStream << s % 60 << ":";
    // ms render 000
    long ms = milliseconds();
    if (ms < 100)
        strStream << 0;
    if (ms < 10)
        strStream << 0;
    strStream << ms % 1000;

    strStream << std::endl;
    return strStream.str();
}


