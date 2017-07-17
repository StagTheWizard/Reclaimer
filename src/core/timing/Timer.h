//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TIMER_H
#define RECLAIMER_TIMER_H


#include <ctime>


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
protected:
private:
    float duration();

    std::clock_t startTime;
};


#endif //RECLAIMER_TIMER_H
