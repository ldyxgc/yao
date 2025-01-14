function(yao__exe NAME)
  add_executable(${NAME} ${NAME}.cpp)
  target_link_libraries(${NAME} yao)
endfunction()

add_subdirectory(cpp)

add_subdirectory(yao)
