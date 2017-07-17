//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TIMER_H
#define RECLAIMER_TIMER_H


#include <ctime>
#include <string>
#include <chrono>


class Timer {
public:
    Timer();
    ~Timer();

    static Timer Start();

    long days();
    long hours();
    long minutes();
    long seconds();
    long milliseconds();

    std::string str();
protected:
private:

    std::chrono::high_resolution_clock::time_point startTime;
};


#endif //RECLAIMER_TIMER_H
