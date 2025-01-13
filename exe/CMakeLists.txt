function(yao__exe NAME)
  add_executable(${NAME} ${NAME}.cpp)
  target_link_libraries(${NAME} yao)
endfunction()

add_subdirectory(yao)

yao__exe(custom_comparator_1)

yao__exe(default_comparator)
