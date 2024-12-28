add_subdirectory(com)

add_subdirectory(def)

add_subdirectory(prt)

add_subdirectory(req)

add_executable(tst__yao__com tst__yao__com.cpp)
target_link_libraries(tst__yao__com yao)
add_test(tst__yao__com tst__yao__com)
