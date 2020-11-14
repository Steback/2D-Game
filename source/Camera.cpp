#include "glm/gtc/matrix_transform.hpp"

#include "Camera.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Constants.hpp"

Camera::Camera(float scale_, float nearPlane_, float farPlane_)
    : position(glm::vec2(0.0f, 0.0f)), scale(scale_), nearPlane(nearPlane_), farPlane(farPlane_) {  }

Camera::~Camera() = default;

glm::mat4 Camera::viewMatrix(glm::vec2 position_) {
    view = glm::mat4(1.0f);
    position = position_;

    if ( Game::state_ == GameGUI::State::Game ) {
        if ( position.y >= Game::map->getTopBorder() - MAX_CAMERA_VIEW_Y ) {
            position.y = Game::map->getTopBorder() - MAX_CAMERA_VIEW_Y;
        }

        if ( position.y <= Game::map->getBottomBorder() + MAX_CAMERA_VIEW_Y ) {
            position.y = Game::map->getBottomBorder() + MAX_CAMERA_VIEW_Y;
        }

        if ( position.x <= Game::map->getLeftBorder() + MAX_CAMERA_VIEW_X ) {
            position.x = Game::map->getLeftBorder() + MAX_CAMERA_VIEW_X;
        }

        if ( position.x >= Game::map->getRightBorder() - MAX_CAMERA_VIEW_X ) {
            position.x = Game::map->getRightBorder() - MAX_CAMERA_VIEW_X;
        }
    }

    return glm::translate(view, glm::vec3(-position, 0.0f));
}

glm::mat4 Camera::projectionMatrix(glm::vec2 windowSize_) const {
    windowSize_.x *= scale;
    windowSize_.y *= scale;

    return glm::ortho(-windowSize_.x, windowSize_.x, -windowSize_.y, windowSize_.y, nearPlane, farPlane);;
}
