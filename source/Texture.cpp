#include "spdlog/spdlog.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.hpp"

Texture::Texture(std::string filePath_) : filePath(std::move(filePath_)) {  }

Texture::~Texture() = default;

bool Texture::loadTexture() {
    int width, height;
    int comp;
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &comp, 4);

    if ( !imageData ) {
        spdlog::error("[Texture] Fail load image: {}", filePath);
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);

    imageSize = glm::vec2(width, height);

    return true;
}

void Texture::useTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint Texture::getTextureID() const {
    return textureID;
}

glm::vec2 Texture::getImageSize() const {
    return imageSize;
}

void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
}
