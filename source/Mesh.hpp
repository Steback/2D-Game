#ifndef MESH_H
#define MESH_H

#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

struct Vertex {
    glm::vec2 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    Vertex(const glm::vec2& pos_, const glm::vec3& color_, const glm::vec2& texCoord_)
        : position(pos_), color(color_), texCoord(texCoord_) {  }
};

class Mesh {
    public:
        Mesh(const std::vector<Vertex>&  vertices_, const std::vector<GLuint>&  indices_);
        ~Mesh();
        void renderMesh() const;
        void setTextureCoords(std::vector<glm::vec2> textureCoords_);

    private:
        GLuint VAO{}, VBO[3]{}, IBO{};
        GLuint indexCount;

        void createMesh(const std::vector<Vertex>& vertices_, const std::vector<GLuint>& indices_);
};

#endif
