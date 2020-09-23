#include "glm/gtc/matrix_transform.hpp"

#include "Camera.hpp"

Camera::Camera(float scale_, float nearPlane_, float farPlane_)
    : position(glm::vec2(0.0f, 0.0f)), scale(scale_), nearPlane(-1.0f), farPlane(1.0f) {  }

Camera::~Camera() = default;

glm::mat4 Camera::viewMatrix(glm::vec2 position_) {
    view = glm::mat4(1.0f);
    position = position_;

    return glm::translate(view, glm::vec3(-position, 0.0f));
}

glm::mat4 Camera::projectionMatrix(glm::vec2 windowSize_) const {
    windowSize_.x /= scale;
    windowSize_.y /= scale;

    return glm::ortho(-windowSize_.x, windowSize_.x, -windowSize_.y, windowSize_.y, nearPlane, farPlane);;
}
