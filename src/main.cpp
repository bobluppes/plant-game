#include "window_manager.h"
#include "data_manager.h"
#include "shader.h"
#include "data.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const std::string VERTEX_SHADER_SRC{"/home/bluppes/CLionProjects/plant-game/src/shaders/vertex_shader.txt"};
const std::string FRAGMENT_SHADER_SRC{"/home/bluppes/CLionProjects/plant-game/src/shaders/fragment_shader.txt"};

constexpr bool DEBUG_MODE{false};

int main() {

    // Create a new output window
    WindowManager window_manager{"Plant Game"};

    // Load all data into a new datamodel
    DataManager data_manager{};
    data_manager.load_textures(textures);
    data_manager.load_vertex_data(cube_vertices, sizeof(cube_vertices));

    // Create a shader object and compile/link the vertex and fragment shaders
    Shader shader{VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC};
    shader.compile_program();

    // Set the locations of the two textures in the shader
    shader.use();
    shader.set_int("texture1", 0);
    shader.set_int("texture2", 1);

    glEnable(GL_DEPTH_TEST);

    while(!window_manager.should_close())
    {

        window_manager.process_input(shader);

        // Rendering
        window_manager.clear();

        data_manager.bind();

        window_manager.prepare_next_frame(shader);

        if constexpr(DEBUG_MODE) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        for (int i{0}; i < 10; ++i) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_positions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle) / 5.0f, glm::vec3(1.0f, 0.3f, 0.5f));
            shader.set_mat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        window_manager.render();

        data_manager.unbind();
    }

    return 0;
}
