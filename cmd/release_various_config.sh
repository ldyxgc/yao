#!/bin/bash

set -x # Print commands and their arguments as they are executed.

# Option
VAR__CMAKE_BUILD_TYPE=Release
ARR__YAO_CONFIG__OSPRINTF=(
  YAO_CONFIG__OSPRINTF__FUNCTION
  YAO_CONFIG__OSPRINTF__TEMPLATE
)
ARR__YAO_CONFIG__LAB__RE_ERASED_STATE=(
  YAO_CONFIG__LAB__RE_ERASED_STATE__VIRTUAL_FUNCTION
  YAO_CONFIG__LAB__RE_ERASED_STATE__FUNCTION_POINTER
  YAO_CONFIG__LAB__RE_ERASED_STATE__FUNCTION_OBJECT
)

# Loop
for YAO_CONFIG__OSPRINTF in ${ARR__YAO_CONFIG__OSPRINTF[@]}; do
for YAO_CONFIG__LAB__RE_ERASED_STATE in ${ARR__YAO_CONFIG__LAB__RE_ERASED_STATE[@]}; do

# Clean
rm -rf build

# Config
cmake -B build \
  $@ \
  -D CMAKE_BUILD_TYPE=${VAR__CMAKE_BUILD_TYPE} \
  -D YAO_CONFIG__OSPRINTF=${YAO_CONFIG__OSPRINTF} \
  -D YAO_CONFIG__LAB__RE_ERASED_STATE=${YAO_CONFIG__LAB__RE_ERASED_STATE}
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
done
