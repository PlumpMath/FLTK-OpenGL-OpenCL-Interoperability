cmake_minimum_required(VERSION 2.8)
project(FLTK-Test)

add_subdirectory(OpenCLUtilityLibrary)
find_package(OpenCLUtilityLibrary PATHS "${FLTK-Test_BINARY_DIR}/OpenCLUtilityLibrary" REQUIRED)
include(${OpenCLUtilityLibrary_USE_FILE})

find_package(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS})

add_executable(test main.cpp)
target_link_libraries(test OpenCLUtilityLibrary ${FLTK_LIBRARIES})