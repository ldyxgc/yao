cmake_minimum_required(VERSION 3.31.3)

project(yao)

add_library(yao)
target_include_directories(yao PUBLIC inc)
file(GLOB_RECURSE YAO_SRC src/*.cpp)
target_sources(yao PRIVATE ${YAO_SRC})

add_subdirectory(exe)
