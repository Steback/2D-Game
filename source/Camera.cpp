#include "glm/gtc/matrix_transform.hpp"

#include "Camera.hpp"

Camera::Camera(glm::vec3 position_) : position(position_), nearPlane(0.0f), farPlane(100.0f) {  }

Camera::~Camera() = default;

glm::mat4 Camera::viewMatrix(glm::vec3 center_) {
    return glm::lookAt(position, center_, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::projectionMatrix(float fov_, glm::vec2 windowSize_) const {
    return glm::perspective(fov_, windowSize_.x / windowSize_.y, nearPlane, farPlane);
}

void Camera::setCamPosition(glm::vec2 position_) {
    position = glm::vec3(position_, position.z);
}
