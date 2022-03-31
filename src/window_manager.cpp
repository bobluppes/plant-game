#include "window_manager.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

        WindowManager *wm = static_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        if (wm->firstMouse) // initially set to true
        {
            wm->lastX = xpos;
            wm->lastY = ypos;
            wm->firstMouse = false;
        }

        float x_offset = xpos - wm->lastX;
        float y_offset = wm->lastY - ypos; // reversed since y-coordinates range from bottom to top
        wm->lastX = xpos;
        wm->lastY = ypos;

        const float sensitivity = 0.1f;
        x_offset *= sensitivity;
        y_offset *= sensitivity;

        wm->yaw   += x_offset;
        wm->pitch += y_offset;

        if(wm->pitch > 89.0f)
            wm->pitch =  89.0f;
        if(wm->pitch < -89.0f)
            wm->pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(wm->yaw)) * cos(glm::radians(wm->pitch));
        direction.y = sin(glm::radians(wm->pitch));
        direction.z = sin(glm::radians(wm->yaw)) * cos(glm::radians(wm->pitch));
        wm->cameraFront = glm::normalize(direction);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

        WindowManager *wm = static_cast<WindowManager *>(glfwGetWindowUserPointer(window));

        wm->fov_ -= (float)yoffset;
        if (wm->fov_ < 1.0f)
            wm->fov_ = 1.0f;
        if (wm->fov_ > 45.0f)
            wm->fov_ = 45.0f;
    }

}

WindowManager::WindowManager(const std::string& title) {

    // Initialize OpenGL to version 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a new window
    window_ = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), nullptr, nullptr);
    if (!window_)
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

    // Hide the cursor and capture it
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(window_, this);

    glfwSetCursorPosCallback(window_, mouse_callback);
    glfwSetScrollCallback(window_, scroll_callback);

}

WindowManager::~WindowManager() {
    glfwTerminate();
}

bool WindowManager::should_close() {
    return glfwWindowShouldClose(window_);
}

void WindowManager::process_input(Shader& shader) {
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
}

void WindowManager::clear() {
    glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::prepare_next_frame(Shader& shader) {
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    shader.set_mat4("model", model);

    auto view {glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)};
    shader.set_mat4("view", view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(fov_), 1920.0f / 1000.0f, 0.1f, 100.0f);
    shader.set_mat4("projection", projection);
}

void WindowManager::render() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwSwapBuffers(window_);
    glfwPollEvents();
}