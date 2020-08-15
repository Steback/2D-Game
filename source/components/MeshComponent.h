#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "../Mesh.hpp"

class MeshComponent {
    public:
        std::unique_ptr<Mesh> mesh;

        MeshComponent(const std::vector<Shape>& vertices_, const std::vector<GLuint>& indices_) {
            mesh = std::make_unique<Mesh>(vertices_, indices_);
        }

        ~MeshComponent() {
            mesh->clearMesh();
        }

        void render() const {
            mesh->renderMesh();
        }

};

#endif
