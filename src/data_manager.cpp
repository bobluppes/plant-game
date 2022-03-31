#include "data_manager.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

DataManager::DataManager() {
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
}

DataManager::~DataManager() {
    glDeleteVertexArrays(1, &VAO_);

    for (auto buffer: buffers_) {
        glDeleteBuffers(1, &buffer);
    }

    for (auto texture: textures_) {
        glDeleteTextures(1, &texture);
    }
}

void DataManager::load_vertex_data(const float* vertices, std::size_t vertex_size) {
    auto vbo_id{create_vbo()};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices, GL_STATIC_DRAW);

    // Vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void DataManager::load_element_data(const unsigned int* elements, std::size_t size) {
    auto vbo_id{create_vbo()};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elements, GL_STATIC_DRAW);
}

void DataManager::load_textures(const std::vector<std::string>& source_files) {
    for (auto& source_file: source_files) {
        textures_.emplace_back(load_texture(source_file));
    }

}

void DataManager::bind() {
    glBindVertexArray(VAO_);

    for (int i{0}; i < textures_.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[i]);
    }
}

void DataManager::unbind() {
    glBindVertexArray(0);
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

unsigned int DataManager::create_vbo() {
    unsigned int vbo_id;
    glGenBuffers(1, &vbo_id);
    buffers_.emplace_back(vbo_id);
    return vbo_id;
}

