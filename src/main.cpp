#include <iostream>
#include <math.h>

#include "window_manager.h"
#include "data_manager.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const std::string VERTEX_SHADER_SRC{"/home/bluppes/CLionProjects/plant-game/src/shaders/vertex_shader.txt"};
const std::string FRAGMENT_SHADER_SRC{"/home/bluppes/CLionProjects/plant-game/src/shaders/fragment_shader.txt"};

float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

const unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

int main() {

    WindowManager window_manager{"Plant Game"};

    DataManager data_manager{};

    data_manager.load_textures({"/home/bluppes/CLionProjects/plant-game/graphics/container.jpg", "/home/bluppes/CLionProjects/plant-game/graphics/awesomeface.png"});

    auto vao_id{data_manager.load_data(vertices, sizeof(vertices), indices, sizeof(indices))};

    Shader shader{VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC};

    try {
        shader.compile_program();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    shader.use();
    shader.set_int("texture1", 0);
    shader.set_int("texture2", 1);

    auto default_mix_val = 0.5f;
    shader.set_float("mix_value", default_mix_val);

    while(!window_manager.should_close())
    {

        window_manager.process_input(shader, default_mix_val);

        // Rendering
        glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        data_manager.bind_textures();

        shader.use();

        glBindVertexArray(vao_id);

        auto trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.set_mat4("transform", trans);


        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        auto trans2 = glm::mat4(1.0f);
        auto scale_factor{sin((float)glfwGetTime()) + 1};
        trans2 = glm::scale(trans2, glm::vec3(scale_factor, scale_factor, scale_factor));
        trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
        shader.set_mat4("transform", trans2);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        window_manager.render();
    }

    glfwTerminate();

    return 0;
}
