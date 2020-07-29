#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {
    public:
        Window();
        ~Window();
        void init(int width_, int height_);
        void render();
        void destroy();
        bool isRunning();
        void swapBuffer();

    private:
        GLFWwindow* window;
        int width, height;
};

#endif
