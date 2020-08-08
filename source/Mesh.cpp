#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Shape>& vertices_, const std::vector<GLuint>& indices_) : indexCount(indices_.size()) {
    createMesh(vertices_, indices_);
}

Mesh::~Mesh() = default;

void Mesh::createMesh(const std::vector<Shape>& vertices_, const std::vector<GLuint>& indices_) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_[0]) * indices_.size(), &indices_[0], GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_[0]) * vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)(sizeof(vertices_[0].position)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)(sizeof(vertices_[0].color) + sizeof(vertices_[0].position)));
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

void Mesh::clearMesh() {
    if ( IBO != 0 ) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if ( VBO != 0 ) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if ( VAO != 0 ) {
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}
