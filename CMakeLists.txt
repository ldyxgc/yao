cmake_minimum_required(VERSION 3.31.3)

project(yao)

set(CMAKE_CXX_STANDARD 20)

message("CMAKE_VERSION = ${CMAKE_VERSION}")
message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message("CMAKE_CONFIGURATION_TYPES = ${CMAKE_CONFIGURATION_TYPES}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(
  "CMAKE_CXX:\n"
  "  CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}\n"
  "  CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}\n"
  "  CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}\n"
  "  CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}\n"
  "  CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}"
)

add_library(yao)
target_include_directories(yao PUBLIC inc)
file(GLOB_RECURSE YAO_SRC src/*.cpp)
target_sources(yao PRIVATE ${YAO_SRC})

add_subdirectory(exe)

enable_testing()
add_subdirectory(tst)
