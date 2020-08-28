#ifndef MESH_COMPONENT_HPP
#define MESH_COMPONENT_HPP

#include "../Mesh.hpp"

class MeshComponent {
    public:
        Mesh mesh;

        MeshComponent(const std::vector<Vertex>& vertices_, const std::vector<GLuint>& indices_)
            : mesh(vertices_, indices_) {  }

        ~MeshComponent() = default;

        void render() const {
            mesh.renderMesh();
        }

};

#endif
