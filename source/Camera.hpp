#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include "glm/glm.hpp"

class Camera {
    public:
        explicit Camera(glm::vec3 position_);
        ~Camera();
        glm::mat4 viewMatrix(glm::vec3 center_);
        glm::mat4 projectionMatrix(float fov_, glm::vec2 windowSize_) const;

    private:
        glm::vec3 position;
        glm::vec2 up;
        float nearPlane;
        float farPlane;
};

#endif
