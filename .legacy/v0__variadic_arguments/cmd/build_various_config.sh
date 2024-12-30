#!/bin/bash

set -x # Print commands and their arguments as they are executed.
set -e # Exit immediately if a command exits with a non-zero status.

# Option
ARR__YAO_CONFIG__PRINT_FORMAT=(
  YAO_CONFIG__PRINT_FORMAT__FUNCTION
  YAO_CONFIG__PRINT_FORMAT__TEMPLATE
)

# Iterate
for YAO_CONFIG__PRINT_FORMAT in ${ARR__YAO_CONFIG__PRINT_FORMAT[@]} ; do

bash \
  $(dirname ${BASH_SOURCE[0]})/build_default_config.sh \
    $@ \
    -D YAO_CONFIG__PRINT_FORMAT=${YAO_CONFIG__PRINT_FORMAT}

done
