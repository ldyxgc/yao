if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_executable(tst__yao__prt__impl__func__print_format____nullptr tst__yao__prt__impl__func__print_format____nullptr.cpp)
  target_link_libraries(tst__yao__prt__impl__func__print_format____nullptr yao)
  add_test(NAME tst__yao__prt__impl__func__print_format____nullptr COMMAND cmake -E env $<TARGET_FILE:tst__yao__prt__impl__func__print_format____nullptr>)
  set_tests_properties(tst__yao__prt__impl__func__print_format____nullptr PROPERTIES WILL_FAIL TRUE)
endif()

add_executable(tst__yao__prt__impl__func__print_format tst__yao__prt__impl__func__print_format.cpp)
target_link_libraries(tst__yao__prt__impl__func__print_format yao)
add_test(tst__yao__prt__impl__func__print_format tst__yao__prt__impl__func__print_format)
