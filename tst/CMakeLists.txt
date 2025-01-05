function(yao__tst NAME)
  add_executable(${NAME} ${NAME}.cpp)
  target_link_libraries(${NAME} yao)
  add_test(NAME ${NAME} COMMAND cmake -E env $<TARGET_FILE:${NAME}>)
endfunction()

add_subdirectory(cpp)

add_subdirectory(yao)
