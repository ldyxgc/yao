cmake_minimum_required(VERSION 3.28.3)

project(yao)

if((NOT DEFINED CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL ""))
  set(CMAKE_BUILD_TYPE Debug)
elseif(NOT ((CMAKE_BUILD_TYPE STREQUAL "Debug") OR
            (CMAKE_BUILD_TYPE STREQUAL "Release")))
  message(FATAL_ERROR "CMAKE_BUILD_TYPE: should be \"Debug\" or \"Release\"")
endif()

add_library(yao INTERFACE)
include(config.cmake) # ${PROJECT_SOURCE_DIR}/inc/yao/config.hpp
target_include_directories(yao INTERFACE inc)

add_subdirectory(exe)

enable_testing()
add_subdirectory(tst)
