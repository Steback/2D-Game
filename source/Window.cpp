#include "spdlog/spdlog.h"

#include "Window.hpp"

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

bool* Window::getKeys() {
    return keys;
}

void Window::keyboardCallback(GLFWwindow *window_, int key_, int scanCode_, int action_, int mods_) {
    auto* w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));

    if ( key_ >= 0 && key_ < 1024 ) {
        if ( action_ == GLFW_PRESS ) {
            w->keys[key_] = true;
        } else if ( action_ == GLFW_RELEASE ) {
            w->keys[key_] = false;
        }
    }
}

void Window::windowShouldClose(bool close_) {
    if ( close_ ) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
