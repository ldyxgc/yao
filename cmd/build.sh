#!/bin/bash

set -x # Print commands and their arguments as they are executed.
set -e # Exit immediately if a command exits with a non-zero status.

# Config
cmake -B build $@

# Option
CMAKE_BUILD_TYPE=$(cmake -L -N build | grep CMAKE_BUILD_TYPE | cut -d '=' -f 2)

# Build
cmake --build build --config ${CMAKE_BUILD_TYPE}

# Test
ctest --test-dir build --build-config ${CMAKE_BUILD_TYPE}
