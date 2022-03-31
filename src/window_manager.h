#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

class WindowManager {
public:

    explicit WindowManager(const std::string& title);

    ~WindowManager();

    bool should_close();

    void process_input(Shader& shader);

    void clear();

    void render();

private:

    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);

    constexpr static auto WIDTH{800};
    constexpr static auto HEIGHT{600};

    GLFWwindow* window_;

};