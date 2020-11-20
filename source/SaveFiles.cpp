#include <fstream>

#include "cereal/archives/json.hpp"

#include "SaveFiles.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"
#include "components/TransformComponent.hpp"


struct Position {
    float x, y;

    template<class Archive>
    void serialize(Archive & archive) {
        archive(CEREAL_NVP(x), CEREAL_NVP(y));
    }
};


void SaveFile::save(const std::string &filename, Entity player) {
    std::ofstream os("saves/" + filename + ".json");
    cereal::JSONOutputArchive archive(os);

    auto playerPosition = Game::entityManager->registry.get<TransformComponent>(player.entity).position;

    Position position{playerPosition.x, playerPosition.y};

    archive(CEREAL_NVP(position));
}

void SaveFile::load(const std::string &filename, Entity player) {
    std::ifstream os("saves/" + filename + ".json");
    cereal::JSONInputArchive archive(os);

    auto& playerPosition = Game::entityManager->registry.get<TransformComponent>(player.entity).position;

    Position position{};

    archive(CEREAL_NVP(position));

    playerPosition = glm::vec2(position.x, position.y);
}
