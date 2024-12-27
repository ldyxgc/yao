cmake_minimum_required(VERSION 3.29)

project(yao)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING
  "The available build types on multi-config generators" FORCE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
  "The build type on single-config generators" FORCE)
if(CMAKE_BUILD_TYPE STREQUAL "")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Debug)
elseif(NOT CMAKE_BUILD_TYPE IN_LIST CMAKE_CONFIGURATION_TYPES)
  message(FATAL_ERROR "CMAKE_BUILD_TYPE not in ${CMAKE_CONFIGURATION_TYPES}")
endif()

message("CMAKE_VERSION = ${CMAKE_VERSION}")
message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message("CMAKE_CONFIGURATION_TYPES = ${CMAKE_CONFIGURATION_TYPES}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

add_library(yao INTERFACE)
include(config.cmake) # ${PROJECT_SOURCE_DIR}/inc/yao/config.hpp
target_include_directories(yao INTERFACE inc)

add_subdirectory(exe)

enable_testing()
add_subdirectory(tst)
