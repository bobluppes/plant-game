#pragma once

#include <cstdlib>
#include <string>
#include <vector>

#include <glad/glad.h>

class DataManager {
public:

    /**
     * An instance of a DataManager wraps a single OpenGL VertexArrayObject
     */
    DataManager();

    ~DataManager();

    void load_vertex_data(const float* vertices, std::size_t size);

    void load_element_data(const unsigned int* elements, std::size_t size);

    void load_textures(const std::vector<std::string>& source_files);

    void bind();

    void unbind();

private:
    unsigned int create_vbo();

    unsigned int load_texture(const std::string& source_file);

    std::vector<unsigned int> textures_;

    std::vector<unsigned int> buffers_;

    // The underlying VAO object ID
    unsigned int VAO_{};
};