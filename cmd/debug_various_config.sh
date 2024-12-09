#!/bin/bash

set -x # Print commands and their arguments as they are executed.

# Option
VAR__CMAKE_BUILD_TYPE=Debug
ARR__YAO_CONFIG__OSPRINTF=(YAO_CONFIG__OSPRINTF__FUNCTION YAO_CONFIG__OSPRINTF__TEMPLATE)

# Loop
for YAO_CONFIG__OSPRINTF in ${ARR__YAO_CONFIG__OSPRINTF[@]}; do

# Clean
rm -rf build

# Config
cmake -B build \
  $@ \
  -D CMAKE_BUILD_TYPE=${VAR__CMAKE_BUILD_TYPE} \
  -D YAO_CONFIG__OSPRINTF=${YAO_CONFIG__OSPRINTF}
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

done
