cmake_minimum_required(VERSION 2.8)
project(FLTK-Test)

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

add_executable(test main.cpp)
target_link_libraries(test ${FLTK_LIBRARIES})