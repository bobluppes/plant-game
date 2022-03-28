#include <iostream>

#include "window_manager.h"
#include "data_manager.h"
#include "shader.h"

const std::string VERTEX_SHADER_SRC{"/home/bluppes/CLionProjects/plant-game/src/shaders/vertex_shader.txt"};
const std::string FRAGMENT_SHADER_SRC{"/home/bluppes/CLionProjects/plant-game/src/shaders/fragment_shader.txt"};

const float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};

const unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

int main() {

    WindowManager window_manager{"Plant Game"};

    DataManager data_manager{};

    auto vao_id{data_manager.loadData(vertices, sizeof(vertices), indices, sizeof(indices))};

    Shader shader{};
    unsigned int shader_program;

    try {
        shader_program = shader.createProgram(VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC);
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    while(!window_manager.should_close())
    {
        window_manager.process_input();

        // Rendering
        glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao_id);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window_manager.render();
    }

    glfwTerminate();

    return 0;
}
