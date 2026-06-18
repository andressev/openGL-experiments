#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <cmath>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float speed;

    glm::vec3 orbitCenter;
    enum class CameraMode { Orbit, Free };
    CameraMode mode;

    Camera()
        : position(0.0f, 0.0f, 3.0f),
          front(0.0f, 0.0f, -1.0f),
          up(0.0f, 1.0f, 0.0f),
          speed(1.5f),
          deltaTime(0.0f),
          lastTime(0.0f),
          mode(CameraMode::Free),
          orbitAngle(0.0f),
          orbitRadius(3.0f)
    {}

    void processInput(GLFWwindow* window) {
        float currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        float cameraSpeed = speed * deltaTime;

        if (mode == CameraMode::Orbit)
            orbitMode(window, cameraSpeed);
        if (mode == CameraMode::Free)
            freeMode(window, cameraSpeed);
    }

    void freeMode(GLFWwindow* window, float cameraSpeed) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += cameraSpeed * front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= cameraSpeed * front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

        //TODO free rotation
    }

    void orbitMode(GLFWwindow* window, float cameraSpeed) {
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            orbitAngle -= cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            orbitAngle += cameraSpeed;

        position.x = orbitCenter.x + orbitRadius * sin(orbitAngle);
        position.z = orbitCenter.z + orbitRadius * cos(orbitAngle);
        front = glm::normalize(orbitCenter - position);
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

private:
    float deltaTime;
    float lastTime;
    float orbitAngle;
    float orbitRadius;
};

#endif
