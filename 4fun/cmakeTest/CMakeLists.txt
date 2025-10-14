cmake_minimum_required(VERSION 3.15)
project(cmakeTest C)


add_subdirectory(mylib)

add_executable(cmakeTest main.c)

target_link_libraries(cmakeTest PRIVATE mylib)

