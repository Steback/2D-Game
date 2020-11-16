#include "spdlog/spdlog.h"

#include "Window.hpp"
#include "Game.hpp"
#include "gui/Gui.hpp"

static void MouseFunc(GLFWwindow *window, int button, int state, int mode) {
    double dx, dy;

    glfwGetCursorPos(window, &dx, &dy);

    int x = static_cast<int>(dx);
    int y = static_cast<int>(dy);

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (state == GLFW_PRESS) {
            Game::gui->m_view->MouseButtonDown(x, y, Noesis::MouseButton_Left);
        } else if (state == GLFW_RELEASE) {
            Game::gui->m_view->MouseButtonUp(x, y, Noesis::MouseButton_Left);
        }
    }
}


Window::Window() : window(nullptr), width(0), height(0) {  }

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::init(int width_, int height_) {
    spdlog::info("[GLFW] Init");

    if ( !glfwInit() ) {
        spdlog::error("[GLFW] Error Initialising\n");
        glfwTerminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width_, height_, "2D Game", nullptr, nullptr);

    if ( !window ) {
        spdlog::error("[GLFW] Failed to create window\n");
        glfwTerminate();
        return ;
    }

    glfwGetFramebufferSize(window, &width, &height);

    glfwSetKeyCallback(window, keyboardCallback);

    glfwMakeContextCurrent(window);

    spdlog::info("[Glad] Init");

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
        spdlog::error("[Glad] Failed to initialize\n");
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, MouseFunc);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::render() {
    glfwPollEvents();

    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(window);
}

void Window::swapBuffer() {
    glfwSwapBuffers(window);
}

glm::vec2 Window::windowSize() const {
    return glm::vec2(width, height);
}

glm::vec2 Window::cursorPos() const {
    double dx, dy;

    glfwGetCursorPos(window, &dx, &dy);

    return glm::vec2(static_cast<float>(dx), static_cast<float>(dy));
}

bool* Window::getKeys() {
    return keys;
}

void Window::keyboardCallback(GLFWwindow *window_, int key_, int scanCode_, int action_, int mods_) {
    auto* w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));

    if ( key_ >= 0 && key_ < 1024 ) {
        if ( action_ == GLFW_PRESS ) {
            w->keys[key_] = true;
            Game::gui->m_view->KeyDown(Gui::getKeyCode(key_));
        } else if ( action_ == GLFW_RELEASE ) {
            w->keys[key_] = false;
            Game::gui->m_view->KeyUp(Gui::getKeyCode(key_));
        }
    }
}

void Window::windowShouldClose(bool close_) {
    if ( close_ ) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}