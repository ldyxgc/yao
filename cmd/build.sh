#!/bin/bash

set -x # Print commands and their arguments as they are executed.
set -e # Exit immediately if a command exits with a non-zero status.

# Config
time \
cmake -B build

# Build
time \
cmake --build build

# Test
time \
ctest --test-dir build
