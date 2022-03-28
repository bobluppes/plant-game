#pragma once

#include <cstdlib>

#include <glad/glad.h>

class DataManager {
public:

    DataManager();

    ~DataManager();

    unsigned int loadData(const float* vertices, std::size_t vertex_size, const unsigned int* indices, std::size_t index_size);

private:
    unsigned int createVAO();
    unsigned int createVBO();
};