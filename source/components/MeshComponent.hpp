#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "../Mesh.hpp"

class MeshComponent {
    public:
        Mesh mesh;

        MeshComponent(const std::vector<Vertex>& vertices_, const std::vector<GLuint>& indices_)
            : mesh(vertices_, indices_){  }

        ~MeshComponent() {
            mesh.clearMesh();
        }

        void render() const {
            mesh.renderMesh();
        }

};

#endif
