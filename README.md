# 幺 - Yao

## 指令 - Command

``` shell
cmake -B build
# -D CMAKE_BUILD_TYPE=Release
# -D CMAKE_CXX_COMPILER=c++

cmake --build build
# --config Release
# -j, --parallel

ctest --test-dir build
# --build-config Release
# -j, --parallel

cmake -B build && cmake --build build && ctest --test-dir build
```
