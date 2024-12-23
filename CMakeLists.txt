cmake_minimum_required(VERSION 3.30.2)

project(yao)

set(CMAKE_CXX_STANDARD 20)

add_library(yao)
target_include_directories(yao PUBLIC inc)
file(GLOB_RECURSE YAO_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.cpp)
target_sources(yao PRIVATE ${YAO_SRC})

add_subdirectory(exe)
