add_library(mylib
  src/utils.c
)

target_include_directories(mylib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
