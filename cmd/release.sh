#!/bin/bash

set -x # Print commands and their arguments as they are executed.

# Option
VAR__CMAKE_BUILD_TYPE=Release

# Clean
rm -rf build

# Config
cmake -B build \
  $@ \
  -D CMAKE_BUILD_TYPE=${VAR__CMAKE_BUILD_TYPE}
if [ $? -ne 0 ]; then exit 1; fi

# Build
cmake --build build \
  --config ${VAR__CMAKE_BUILD_TYPE} \
  --parallel
if [ $? -ne 0 ]; then exit 1; fi

# Test
ctest --test-dir build \
  --build-config ${VAR__CMAKE_BUILD_TYPE} \
  --parallel
if [ $? -ne 0 ]; then exit 1; fi
