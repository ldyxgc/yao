#!/bin/bash

set -x # Print commands and their arguments as they are executed.
set -e # Exit immediately if a command exits with a non-zero status.

# Config
cmake -B build

# Build
cmake --build build

# Test
ctest --test-dir build