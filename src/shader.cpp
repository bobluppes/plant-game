#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <cstring>

namespace {
    std::string read_file(const std::string& src_file) {
        std::ifstream stream{src_file};
        std::stringstream buffer;
        buffer << stream.rdbuf();
        return buffer.str();
    }

    void check_compile_errors(unsigned int shader_id) {
        int  success{0};
        char infoLog[512];
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
            throw std::runtime_error(infoLog);
        }
    }

    void check_link_errors(unsigned int program_id) {
        int  success{0};
        char infoLog[512];
        glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(program_id, 512, NULL, infoLog);
            throw std::runtime_error(infoLog);
        }
    }
}

Shader::Shader() {}

Shader::~Shader() {
    for (auto shader_id: shaders_) {
        glDeleteShader(shader_id);
    }
}

unsigned int Shader::createProgram(const std::string& vertex_shader_src, const std::string& fragment_shader_src) {
    auto vertex_shader_id{load_vertex_shader(vertex_shader_src)};
    auto fragment_shader_id{load_fragment_shader(fragment_shader_src)};

    auto shader_program_id{glCreateProgram()};
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);

    link_shaders(shader_program_id);

    return shader_program_id;
}

unsigned int Shader::load_vertex_shader(const std::string& vertex_shader_src) {
    // TODO: fix this redundant step
    auto vertex_shader{read_file(vertex_shader_src)};
    auto vertex_shader_str{vertex_shader.c_str()};

    auto vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &(vertex_shader_str), NULL);
    glCompileShader(vertex_shader_id);

    check_compile_errors(vertex_shader_id);

    shaders_.emplace_back(vertex_shader_id);

    return vertex_shader_id;
}

unsigned int Shader::load_fragment_shader(const std::string& fragment_shader_src) {
    // TODO: fix this redundant step
    auto fragment_shader{read_file(fragment_shader_src)};
    auto fragment_shader_str{fragment_shader.c_str()};

    auto fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &(fragment_shader_str), NULL);
    glCompileShader(fragment_shader_id);

    check_compile_errors(fragment_shader_id);

    shaders_.emplace_back(fragment_shader_id);

    return fragment_shader_id;
}

void Shader::link_shaders(unsigned int program_id) {
    glLinkProgram(program_id);
    check_link_errors(program_id);
}