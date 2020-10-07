#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>&  vertices_, const std::vector<GLuint>&  indices_)
    :  indexCount(indices_.size()) {
    createMesh(vertices_, indices_);
}

Mesh::~Mesh() {
    if ( IBO != 0 ) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if ( VBO[0] != 0 ) {
        glDeleteBuffers(3, VBO);
    }

    if ( VAO != 0 ) {
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }
}

void Mesh::createMesh(const std::vector<Vertex>& vertices_, const std::vector<GLuint>& indices_) {
    std::vector<glm::vec2> verticesPositions {
            vertices_[0].position,
            vertices_[1].position,
            vertices_[2].position,
            vertices_[3].position
    };

    std::vector<glm::vec3> verticesColor {
            vertices_[0].color,
            vertices_[1].color,
            vertices_[2].color,
            vertices_[3].color
    };

    std::vector<glm::vec2> verticesTextCords{
            vertices_[0].texCoord,
            vertices_[1].texCoord,
            vertices_[2].texCoord,
            vertices_[3].texCoord
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_[0]) * indices_.size(), &indices_[0], GL_STATIC_DRAW);

    glGenBuffers(3, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPositions[0]) * vertices_.size(), &verticesPositions[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(verticesPositions[0]), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor[0]) * vertices_.size(), &verticesColor[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(verticesColor[0]), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTextCords[0]) * vertices_.size(), &verticesTextCords[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(verticesTextCords[0]), nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::renderMesh() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::setTextureCoords(std::vector<glm::vec2> textureCoords_) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords_[0]) * textureCoords_.size(), &textureCoords_[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
