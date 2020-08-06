#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

class Texture {
    public:
        explicit Texture(std::string filePath_);
        ~Texture();
        bool loadTexture();
        void useTexture() const;
        GLuint getTextureID() const;
        glm::vec2 getImageSize() const;
        void clearTexture();

    private:
        glm::vec2 imageSize;
        GLuint textureID{};
        std::string filePath;
};

#endif
