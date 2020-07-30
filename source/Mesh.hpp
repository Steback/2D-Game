#ifndef MESH_H
#define MESH_H

#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

struct Shape {
    glm::vec2 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    Shape(const glm::vec2& pos_, const glm::vec3& color_, const glm::vec2& texCoord_)
        : position(pos_), color(color_), texCoord(texCoord_) {  }
};

class Mesh {
    public:
        Mesh(const std::vector<Shape>& vertices_, const std::vector<GLuint>& indices_);
        ~Mesh();
        void renderMesh() const;
        void clearMesh();

    private:
        GLuint VAO{}, VBO{}, IBO{};
        GLsizei indexCount{};

        void createMesh(const std::vector<Shape>& vertices_, const std::vector<GLuint>& indices_);
};

#endif
