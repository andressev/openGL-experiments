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
    glm::vec3 orbitCenter;
    float speed;
    enum class CameraMode { Orbit, Free };
    CameraMode mode;

    Camera()
        : position(0.0f, 0.0f, 3.0f),
          front(0.0f, 0.0f, -1.0f),
          up(0.0f, 1.0f, 0.0f),
          orbitCenter(0.f, 0.f,0.f),
          speed(1.5f),
          deltaTime(0.0f),
          lastTime(0.0f),
          mode(CameraMode::Free),
          orbitTheta(0.0f),
          orbitPhi(glm::half_pi<float>()),
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
            orbitTheta -= cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            orbitTheta += cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            orbitPhi -= cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            orbitPhi += cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            orbitRadius += cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            orbitRadius = glm::max(orbitRadius - cameraSpeed, 0.1f);

        // clamp phi away from poles to avoid lookAt singularity
        const float phiMin = 0.05f;
        const float phiMax = glm::pi<float>() - 0.05f;
        orbitPhi = glm::clamp(orbitPhi, phiMin, phiMax);

        position.x = orbitCenter.x + orbitRadius * sin(orbitPhi) * sin(orbitTheta);
        position.y = orbitCenter.y + orbitRadius * cos(orbitPhi);
        position.z = orbitCenter.z + orbitRadius * sin(orbitPhi) * cos(orbitTheta);
        front = glm::normalize(orbitCenter - position);
    }

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

private:
    float deltaTime;
    float lastTime;
    float orbitTheta;
    float orbitPhi;
    float orbitRadius;
};

#endif
