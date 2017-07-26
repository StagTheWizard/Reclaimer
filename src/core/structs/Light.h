//
// Created by montgomery anderson on 25/07/17.
//

#ifndef RECLAIMER_LIGHT_H
#define RECLAIMER_LIGHT_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Light {
    glm::vec4 position;
    glm::vec3 intensities;
    float attenuation;
    float ambientCoefficient;
};

#endif //RECLAIMER_LIGHT_H
