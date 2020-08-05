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
        int getWidth() const;
        int getHeight() const;
        void clearTexture();

    private:
        int width{};
        int height{};
        GLuint textureID{};
        std::string filePath;
};

#endif
