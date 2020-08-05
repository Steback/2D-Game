#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "fmt/core.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

Game::Game() : window(nullptr) {  }

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    shaders.emplace_back( std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag") );

    mesh = std::make_unique<Mesh>( std::vector<Shape> {
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.25f) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.25f) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );

    texture = std::make_unique<Texture>("assets/images/chopper-spritesheet.png");
    texture->loadTexture();
}

float x = 0;

float lastFrame = 0;

void Game::render() {
    glfwPollEvents();

    window->render();
    shaders[0]->useShader();

    glm::mat4 model(1.0f);

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    deltaTime *= 10;

    fmt::print("Deltatime: {}\n", deltaTime);

    x += deltaTime;

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    glUniformMatrix4fv(shaders[0]->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(shaders[0]->getUniformLocation("spriteOffsetX"), x);
    glUniform1i(shaders[0]->getUniformLocation("spriteOffsetY"), 0);
    texture->useTexture();
    mesh->renderMesh();

    if ( x > 1 ) x = 0;

    fmt::print("{}\n", x);

    glUseProgram(0);

    window->swapBuffer();
}

void Game::destroy() {
    mesh->clearMesh();
    shaders[0]->clearShader();
    window->destroy();
}

bool Game::isRunning() {
    return window->isRunning();
}
