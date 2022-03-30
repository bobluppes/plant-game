#pragma once

#include <vector>
#include <string>

class Shader {
public:

    Shader(const std::string& vertex_shader_src, const std::string& fragment_shader_src);

    ~Shader();

    // Throws if an error is encountered during compilation/linking
    void compile_program();

    void use();

    // Utility functions to set uniform variables
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;

private:

    unsigned int load_vertex_shader(const std::string& vertex_shader_src);

    unsigned int load_fragment_shader(const std::string& fragment_shader_src);

    void link_shaders(unsigned int program_id);

    const std::string vertex_shader_src_;
    const std::string fragment_shader_src_;

    std::vector<unsigned int> shaders_;

    unsigned int program_id_;
};