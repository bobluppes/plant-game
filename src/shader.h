#pragma once

#include <vector>
#include <string>

class Shader {
public:

    Shader();

    ~Shader();

    unsigned int createProgram(const std::string& vertex_shader_src, const std::string& fragment_shader_src);

private:

    unsigned int load_vertex_shader(const std::string& vertex_shader_src);

    unsigned int load_fragment_shader(const std::string& fragment_shader_src);

    void link_shaders(unsigned int program_id);

    std::vector<unsigned int> shaders_;
};