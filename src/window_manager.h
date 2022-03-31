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

    void prepare_next_frame(Shader& shader);

    void render();

    // TODO: extract to camera object
    float lastX{WIDTH/2.0f};
    float lastY{HEIGHT/2.0f};

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    float pitch{0.0f};
    float yaw{-90.0f};
    float fov_{45.0f};

    bool firstMouse{true};

private:

    constexpr static auto WIDTH{1920};
    constexpr static auto HEIGHT{1000};

    GLFWwindow* window_;

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

};