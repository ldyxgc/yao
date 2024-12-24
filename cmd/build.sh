#!/bin/bash

set -x # Print commands and their arguments as they are executed.

VAR__CURRENT_DIRECTORY=$(cd $(dirname $0) && pwd)

# Option
# VAR__CMAKE_BUILD_TYPE=Debug

# Clean
rm -rf build

# Config
cmake -B build \
  $@ \
  $(
    if [ -n "${VAR__CMAKE_BUILD_TYPE}" ]; then
      echo -n "-D CMAKE_BUILD_TYPE=${VAR__CMAKE_BUILD_TYPE}"
    fi
  )
if [ $? -ne 0 ]; then exit 1; fi

# Build
cmake --build build \
  $(
    if [ -n "${VAR__CMAKE_BUILD_TYPE}" ]; then
      echo -n "--config ${VAR__CMAKE_BUILD_TYPE}"
    fi
  ) \
  --parallel
if [ $? -ne 0 ]; then exit 1; fi

# Test
ctest --test-dir build \
  $(
    if [ -n "${VAR__CMAKE_BUILD_TYPE}" ]; then
      echo -n "--build-config ${VAR__CMAKE_BUILD_TYPE}"
    fi
  ) \
  --parallel
if [ $? -ne 0 ]; then exit 1; fi
