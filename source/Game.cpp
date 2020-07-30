#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

Game::Game() : window(nullptr) {  }

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    shaders.emplace_back( std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag") );


    mesh = std::make_unique<Mesh>( std::vector<Shape> {
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );
}

void Game::render() {
    glfwPollEvents();

    window->render();
    shaders[0]->useShader();

    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(shaders[0]->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    mesh->RenderMesh();

    glUseProgram(0);

    window->swapBuffer();
}

void Game::destroy() {
    mesh->ClearMesh();
    shaders[0]->clearShader();
    window->destroy();
}

bool Game::isRunning() {
    return window->isRunning();
}
