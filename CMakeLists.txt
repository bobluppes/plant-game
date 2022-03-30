cmake_minimum_required(VERSION 3.21)
project(plant_game)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glad)

include(ExternalProject)
ExternalProject_Add(
        glm
        PREFIX ${CMAKE_BINARY_DIR}/glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        <SOURCE_DIR>/glm ${CMAKE_BINARY_DIR}/installed/glm
        LOG_DOWNLOAD ON
        LOG_INSTALL ON
)

file(GLOB SRC_FILES src/*.h src/*.cpp)

include_directories(includes)

add_executable(plant_game ${SRC_FILES})
target_link_libraries(plant_game glfw glad)
