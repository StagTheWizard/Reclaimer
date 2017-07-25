//
// Created by montgomery anderson on 25/07/17.
//

#ifndef RECLAIMER_SPACIALCHECKS_H
#define RECLAIMER_SPACIALCHECKS_H

namespace extensions {

    bool withinSquareRadius(float x, float y, float rx, float ry, float radius) {
        if (x < rx - radius) return false;
        if (x > rx + radius) return false;
        if (y < ry - radius) return false;
        if (y > ry + radius) return false;
        return true;
    }

}

#endif //RECLAIMER_SPACIALCHECKS_H
