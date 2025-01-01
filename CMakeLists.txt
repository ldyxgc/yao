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

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  string(JOIN " " CMAKE_CXX_FLAGS
    -Wall
    -Wextra
    -Wpedantic

    -Warith-conversion # This affects warnings from -Wconversion
    -Wconversion
    -Wformat=2
    -Wsign-conversion # Disabled by default with -Wconversion
    -Wswitch-default
    -Wswitch-enum
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    string(JOIN " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  string(JOIN " " CMAKE_CXX_FLAGS
    -Weverything

    -Wno-c++98-compat
    -Wno-covered-switch-default
    -Wno-reserved-identifier
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    string(JOIN " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  string(JOIN " " CMAKE_CXX_FLAGS
    -Weverything

    -Wno-c++98-compat-pedantic
    -Wno-covered-switch-default
    -Wno-zero-as-null-pointer-constant
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    string(JOIN " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Werror)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  string(JOIN " " CMAKE_CXX_FLAGS
    /EHsc # Warning C4530 and C4577; Exception handling model

    /Wall

    /wd5045 # Insert Spectre mitigation for memory load
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    string(JOIN " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}
      /WX # Treats all compiler warnings as errors

      /wd4710 # Function marked inline is not inlined by compiler
      /wd4711 # Function not marked inline is inlined by compiler
    )
  endif()
else()
  message(FATAL_ERROR
    "CMAKE_CXX_COMPILER_ID: `${CMAKE_CXX_COMPILER_ID}` is not supported.")
endif()

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

add_library(yao INTERFACE)
include(config.cmake) # ${PROJECT_SOURCE_DIR}/inc/yao/config.hpp
target_include_directories(yao INTERFACE inc)

add_subdirectory(exe)

enable_testing()
add_subdirectory(tst)
