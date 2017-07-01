//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_CAMERA_H
#define RECLAIMER_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <math.h>


class Camera {
public:
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::vec3 upDir = glm::vec3(0, 1, 0);
    glm::vec3 viewDir = glm::vec3(1, 0, 1);
    glm::vec3 viewPt = pos + viewDir;
    glm::vec3 rot = glm::vec3(0, 0, 0);

    float horizontalAngle = (float) M_PI;
    float verticalAngle = 0;
    float initialFOV = 45;

    const float DIRECTIONAL_SPEED = 0.3f;
    const float LATERAL_SPEED = 0.3f;
    const float VERTICAL_SPEED = 0.1f;
    const float ROTATIONAL_SPEED = 0.5f;
    const float MOUSE_SPEED = 0.005f;

    float pitchSensitivity = 0.2f;
    float yawSensitivity = 0.2f;

    Camera();
    Camera(glm::vec3 pos, glm::vec3 upDir, glm::vec3 viewDir);

    void move_forward();
    void move_backwards();
    void strafe_left();
    void strafe_right();
    void move_up();
    void move_down();

protected:
private:
    glm::vec2 screenDimensions;
};


#endif //RECLAIMER_CAMERA_H
