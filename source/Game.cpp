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
            { glm::vec2(-1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec2(0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    } );
}

void Game::render() {
    glfwPollEvents();

    window->render();
    shaders[0]->useShader();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            window->windowSize().x /  window->windowSize().y, 0.1f, 100.0f);

    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(shaders[0]->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shaders[0]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    mesh->RenderMesh();

    glUseProgram(0);

    window->swapBuffer();
}

void Game::destroy() {
    window->destroy();
}

bool Game::isRunning() {
    return window->isRunning();
}
