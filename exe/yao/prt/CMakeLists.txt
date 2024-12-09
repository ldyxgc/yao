add_subdirectory(impl)

add_executable(yao__prt__osprintf yao__prt__osprintf.cpp)
target_link_libraries(yao__prt__osprintf yao)
