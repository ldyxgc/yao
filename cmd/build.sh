#!/bin/bash

set -x # Print commands and their arguments as they are executed.

# Clean
rm -rf build

# Config
cmake -B build \
  $@
if [ $? -ne 0 ]; then exit 1; fi

# Build
cmake --build build \
  --parallel
if [ $? -ne 0 ]; then exit 1; fi

# Test
ctest --test-dir build \
  --parallel
if [ $? -ne 0 ]; then exit 1; fi
