cmake_minimum_required(VERSION 3.28.3)

project(yao)

add_library(yao INTERFACE)
target_include_directories(yao INTERFACE inc)

add_subdirectory(exe)

enable_testing()
add_subdirectory(tst)
