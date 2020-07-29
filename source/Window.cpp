#include "fmt/core.h"

#include "Window.hpp"

Window::Window() : window(nullptr), width(0), height(0) {  }

Window::~Window() = default;

void Window::init(int width_, int height_) {
    if ( !glfwInit() ) {
        fmt::print("Error Initialising GLFW\n");
        return ;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width_, height_, "2D Game", nullptr, nullptr);

    if ( window == nullptr ) {
        fmt::print("Failed to create GLFW window\n");
        destroy();
        return ;
    }

    glfwGetFramebufferSize(window, &width, &height);

    glfwMakeContextCurrent(window);

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
        fmt::print("Failed to initialize GLAD\n");
        destroy();
        return ;
    }
}

void Window::render() {
    glfwPollEvents();

    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::destroy() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::isRunning() {
    return !glfwWindowShouldClose(window);
}

void Window::swapBuffer() {
    glfwSwapBuffers(window);
}
