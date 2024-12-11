cmake_minimum_required(VERSION 3.30.2)

project(yao LANGUAGES CXX)

if((NOT DEFINED CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL ""))
  set(CMAKE_BUILD_TYPE Debug)
elseif(NOT ((CMAKE_BUILD_TYPE STREQUAL "Debug") OR
            (CMAKE_BUILD_TYPE STREQUAL "Release")))
  message(FATAL_ERROR "CMAKE_BUILD_TYPE: should be \"Debug\" or \"Release\"")
endif()
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  string(JOIN " " CMAKE_CXX_FLAGS
    -Wall
    -Wextra
    -Wpedantic

    -Wconversion
    -Wformat=2
    -Wpadded
    -Wsign-conversion # Disabled by default with -Wconversion
    -Wswitch-default
    -Wswitch-enum
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  endif()
elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR
       (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
  string(JOIN " " CMAKE_CXX_FLAGS
    -Weverything

    -Wno-c++98-compat-pedantic
    -Wno-covered-switch-default
    -Wno-reserved-identifier
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  string(JOIN " " CMAKE_CXX_FLAGS
    /EHsc # Warning C4577; Exception handling model

    /Wall

    /wd4710 # Function marked inline is not inlined by compiler
    /wd4711 # Function not marked inline is inlined by compiler
    /wd5045 # Insert Spectre mitigation for memory load
  )
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
  endif()
else()
  message(FATAL_ERROR "CMAKE_CXX_COMPILER_ID: unknown compiler")
endif()

message("CMAKE_VERSION = ${CMAKE_VERSION}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(
  "CMAKE_HOST_SYSTEM:\n"
  "  CMAKE_HOST_SYSTEM = ${CMAKE_HOST_SYSTEM}\n"
  "  CMAKE_HOST_SYSTEM_NAME = ${CMAKE_HOST_SYSTEM_NAME}\n"
  "  CMAKE_HOST_SYSTEM_VERSION = ${CMAKE_HOST_SYSTEM_VERSION}\n"
  "  CMAKE_HOST_SYSTEM_PROCESSOR = ${CMAKE_HOST_SYSTEM_PROCESSOR}"
)
message(
  "CMAKE_SYSTEM:\n"
  "  CMAKE_SYSTEM = ${CMAKE_SYSTEM}\n"
  "  CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}\n"
  "  CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}\n"
  "  CMAKE_SYSTEM_PROCESSOR = ${CMAKE_SYSTEM_PROCESSOR}"
)
message(
  "CMAKE_CXX:\n"
  "  CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}\n"
  "  CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}\n"
  "  CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}\n"
  "  CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}\n"
  "  CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}"
)

include(ProcessorCount)
ProcessorCount(YAO_BUILD__PROCESSOR_COUNT)
message("YAO_BUILD__PROCESSOR_COUNT = ${YAO_BUILD__PROCESSOR_COUNT}")

add_library(yao)
include(config.cmake) # ${CMAKE_CURRENT_SOURCE_DIR}/inc/yao/config.hpp
target_include_directories(yao PUBLIC inc)
file(GLOB_RECURSE YAO_SRC RELATIVE ${CMAKE_CURRENT_LIST_DIR} src/*.cpp)
target_sources(yao PRIVATE ${YAO_SRC})

add_subdirectory(exe)

enable_testing()
add_subdirectory(tst)

unset(CMAKE_BUILD_TYPE CACHE)
