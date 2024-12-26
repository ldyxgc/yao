cmake_minimum_required(VERSION 3.31.3)

project(yao)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING
  "The available build types on multi-config generators" FORCE)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
  "The build type on single-config generators" FORCE)
if(CMAKE_BUILD_TYPE STREQUAL "")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Debug)
elseif(NOT CMAKE_BUILD_TYPE IN_LIST CMAKE_CONFIGURATION_TYPES)
  message(FATAL_ERROR
    "CMAKE_BUILD_TYPE: `${CMAKE_BUILD_TYPE}` is not supported.")
endif()

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
