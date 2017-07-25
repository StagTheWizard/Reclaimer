//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_CAMERA_H
#define RECLAIMER_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <math.h>
#include <glm/mat4x4.hpp>
#include "Constants.h"


class Camera {
public:
    glm::vec3 pos = glm::vec3(-5, 1, -5);
    glm::vec3 upDir = glm::vec3(0, 1, 0);
    glm::vec3 viewDir = glm::vec3(1, 0, 0);
    glm::vec3 viewPt = pos + viewDir;
    glm::vec3 rot = glm::vec3(0, 0, 0);

    float pitch;
    float yaw;
    float initialFOV = 45;

    const float DIRECTIONAL_SPEED = 2.0f;
    const float LATERAL_SPEED = 0.5f;
    const float VERTICAL_SPEED = 0.3f;
    const float ROTATIONAL_SPEED = 0.5f;
    const float MOUSE_SPEED = 0.005f;

    float pitchSensitivity = 0.2f;
    float yawSensitivity = 0.2f;

    Camera();
    Camera(glm::vec3 pos, glm::vec3 upDir, glm::vec3 viewDir);

    glm::mat4 getViewMatrix();

//    void keyPressed(int key, int scanCode, int action, int mods);
    void cursorMoved(double xPos, double yPos);
    void processInput(GLFWwindow *window);

    void moveForward();
    void moveBackwards();
    void strafeLeft();
    void strafeRight();
    void moveUp();
    void moveDown();

protected:
private:
    glm::vec2 screenDimensions;

    bool firstInput = true;
    double lastX = constants::WINDOW_HEIGHT / 2;
    double lastY = constants::WINDOW_WIDTH / 2;
};


#endif //RECLAIMER_CAMERA_H
