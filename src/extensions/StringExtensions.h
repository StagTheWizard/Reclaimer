//
// Created by montgomery anderson on 20/07/17.
//

#ifndef RECLAIMER_STRINGEXTENSIONS_H
#define RECLAIMER_STRINGEXTENSIONS_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

using namespace std;

namespace extensions {


    string toString(float f, int decimalPlaces) {
        string fStr = to_string(f);
        return fStr.substr(0, fStr.find('.') + 1 + decimalPlaces);
    }

    string toString(float f) {
        return toString(f, 4);
    }


    string toString(glm::vec2 vec2, int decimalPlaces) {
        return "(" + toString(vec2.x, decimalPlaces) +
               ", " + toString(vec2.y, decimalPlaces) + ")";
    }


    string toString(glm::vec2 vec2) {
        return toString(vec2, 4);
    }


    string toString(glm::vec3 vec3, int decimalPlaces) {
        return "(" + toString(vec3.x, decimalPlaces) +
               ", " + toString(vec3.y, decimalPlaces) +
               ", " + toString(vec3.z, decimalPlaces) + ")";
    }


    string toString(glm::vec3 vec3) {
        return toString(vec3, 4);
    }


    string toString(glm::vec4 vec4, int decimalPlaces) {
        return "(" + toString(vec4.x, decimalPlaces) +
               ", " + toString(vec4.y, decimalPlaces) +
               ", " + toString(vec4.z, decimalPlaces) +
               ", " + toString(vec4.a, decimalPlaces) + ")";
    }



    string toString(glm::vec4 vec4) {
        return toString(vec4, 4);
    }
}

#endif //RECLAIMER_STRINGEXTENSIONS_H