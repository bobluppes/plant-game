#include "window_manager.h"

#include <iostream>

WindowManager::WindowManager(std::string title) {

    // Initialize OpenGL to version 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a new window
    window_ = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), NULL, NULL);
    if (window_ == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window_);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // Adjust the viewport on window resize
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

}

bool WindowManager::should_close() {
    return glfwWindowShouldClose(window_);
}

void WindowManager::process_input() {
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);
}

void WindowManager::render() {
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}