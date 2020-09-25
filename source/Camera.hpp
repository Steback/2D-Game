#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"

class Camera {
    public:
        Camera(float scale_, float nearPlane_, float farPlane_);
        ~Camera();
        glm::mat4 viewMatrix(glm::vec2 position_);
        [[nodiscard]] glm::mat4 projectionMatrix(glm::vec2 windowSize_) const;

    private:
        glm::vec2 position;
        glm::mat4 view;
        float scale;
        float nearPlane;
        float farPlane;
};

#endif
