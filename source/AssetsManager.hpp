#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <string>
#include <map>
#include <memory>

class Texture;

class AssetsManager {
    public:
        AssetsManager();
        ~AssetsManager();
        void addTexture(const std::string& textureID_, const std::string& filePath_);
        void loadTexture();
        std::shared_ptr<Texture> getTexture(const std::string& textureID_);

    private:
        std::map<std::string, std::shared_ptr<Texture> > textures;
};

#endif
