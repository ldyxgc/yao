#!/bin/bash

set -x # Print commands and their arguments as they are executed.
set -e # Exit immediately if a command exits with a non-zero status.

bash \
  $(dirname ${BASH_SOURCE[0]})/build_various_config.sh \
    $@ \
    -D CMAKE_BUILD_TYPE=Debug
