#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "glm/glm.hpp"

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
        glm::vec2 windowSize() const;
        bool* getKeys();

    private:
        GLFWwindow* window;
        int width, height;
        bool keys[1024]{};

        static void keyboardCallback(GLFWwindow* window_, int key_, int scanCode_, int action_, int mods_);
};

#endif
