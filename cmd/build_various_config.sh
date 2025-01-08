#!/bin/bash

set -x # Print commands and their arguments as they are executed.
set -e # Exit immediately if a command exits with a non-zero status.

# Option
ARR__YAO_CONFIG__RE_ERASED_STATE=(
  YAO_CONFIG__RE_ERASED_STATE__VIRTUAL_FUNCTION
  YAO_CONFIG__RE_ERASED_STATE__FUNCTION_OBJECT
)

# Iterate
for YAO_CONFIG__RE_ERASED_STATE in ${ARR__YAO_CONFIG__RE_ERASED_STATE[@]}; do

bash \
  $(dirname ${BASH_SOURCE[0]})/build_default_config.sh \
    $@ \
    -D YAO_CONFIG__RE_ERASED_STATE=${YAO_CONFIG__RE_ERASED_STATE}

done
