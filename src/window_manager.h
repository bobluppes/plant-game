#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
public:

    explicit WindowManager(std::string title);

    bool should_close();

    void process_input();

    void render();

private:

    void static framebuffer_size_callback(GLFWwindow* window, int width, int height);

    constexpr static auto WIDTH{800};
    constexpr static auto HEIGHT{600};

    GLFWwindow* window_;

};