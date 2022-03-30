cmake_minimum_required(VERSION 3.21)
project(plant_game)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glad)

file(GLOB SRC_FILES src/*.h src/*.cpp)

include_directories(includes)

add_executable(plant_game ${SRC_FILES})
target_link_libraries(plant_game glfw glad)
