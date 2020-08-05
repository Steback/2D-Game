#include "fmt/core.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.hpp"

Texture::Texture(std::string filePath_, bool isAnimated_, int xOffset_, int yOffet_)
    : filePath(std::move(filePath_)), isAnimated(isAnimated_), xOffset(static_cast<float>(xOffset_)), yOffset(
        static_cast<float>(yOffet_)) {  }

Texture::~Texture() = default;

bool Texture::loadTexture() {
    unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, nullptr, 4);

    if ( !imageData ) {
        fmt::print("Fail load image: {}", filePath);
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float colour[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, colour);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);

    return true;
}

void Texture::useTexture() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint Texture::getTextureID() const {
    return textureID;
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

void Texture::clearTexture() {
    glDeleteTextures(1, &textureID);
}
