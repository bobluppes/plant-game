#include "data_manager.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

DataManager::DataManager() {}

DataManager::~DataManager() {
    for (auto buffer: buffers_) {
        glDeleteBuffers(1, &buffer);
    }
}

unsigned int DataManager::load_data(const float* vertices, std::size_t vertex_size, const unsigned int* indices, std::size_t index_size) {
    auto vao_id{createVAO()};
    glBindVertexArray(vao_id);

    auto vbo_id{createVBO()};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices, GL_STATIC_DRAW);

    auto ebo{createVBO()};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, indices, GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    return vao_id;
}

void DataManager::load_textures(const std::vector<std::string>& source_files) {
    for (auto& source_file: source_files) {
        textures_.emplace_back(load_texture(source_file));
    }

}

void DataManager::bind_textures() {
    for (int i{0}; i < textures_.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[i]);
    }
}

unsigned int DataManager::load_texture(const std::string& source_file) {
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // set the texture_id wrapping/filtering options (on the currently bound texture_id object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data{stbi_load(source_file.c_str(), &width, &height, &nrChannels, 0)};

    if (data)
    {
        if (source_file.find(".png") != std::string::npos) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    return texture_id;
}

unsigned int DataManager::createVAO() {
    unsigned int vao_id;
    glGenVertexArrays(1, &vao_id);
    buffers_.emplace_back(vao_id);
    return vao_id;
}

unsigned int DataManager::createVBO() {
    unsigned int vbo_id;
    glGenBuffers(1, &vbo_id);
    buffers_.emplace_back(vbo_id);
    return vbo_id;
}

