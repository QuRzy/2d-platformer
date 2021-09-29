cmake_minimum_required(VERSION 3.17)
project(Game)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS graphics audio REQUIRED)
add_executable(Game main.cpp)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(Game sfml-graphics sfml-audio)