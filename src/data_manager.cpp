#include "data_manager.h"

#include <GLFW/glfw3.h>

DataManager::DataManager() {}

DataManager::~DataManager() {
    // TODO: delete buffers
}

unsigned int DataManager::loadData(const float* vertices, std::size_t vertex_size, const unsigned int* indices, std::size_t index_size) {
    auto vao_id{createVAO()};
    glBindVertexArray(vao_id);

    auto vbo_id{createVBO()};
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices, GL_STATIC_DRAW);

    auto ebo{createVBO()};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return vao_id;
}

unsigned int DataManager::createVAO() {
    unsigned int vao_id;
    glGenVertexArrays(1, &vao_id);
    return vao_id;
}

unsigned int DataManager::createVBO() {
    unsigned int vbo_id;
    glGenBuffers(1, &vbo_id);
    return vbo_id;
}

