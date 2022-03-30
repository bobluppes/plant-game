#pragma once

#include <cstdlib>
#include <string>
#include <vector>

#include <glad/glad.h>

class DataManager {
public:

    DataManager();

    ~DataManager();

    unsigned int load_data(const float* vertices, std::size_t vertex_size, const unsigned int* indices, std::size_t index_size);

    void load_textures(const std::vector<std::string>& source_files);

    void bind_textures();

private:
    unsigned int createVAO();
    unsigned int createVBO();

    unsigned int load_texture(const std::string& source_file);

    std::vector<unsigned int> textures_;

    std::vector<unsigned int> buffers_;
};