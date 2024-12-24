#!/bin/bash

set -x # Print commands and their arguments as they are executed.

VAR__CURRENT_DIRECTORY=$(cd $(dirname $0) && pwd)

# Option
VAR__CMAKE_BUILD_TYPE=Debug

source ${VAR__CURRENT_DIRECTORY}/build.sh
