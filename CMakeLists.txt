cmake_minimum_required(VERSION 3.25)

project(DSA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(cmake/ClangFormat.cmake)

set(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLES
  ${PROJECT_SOURCE_DIR}/data_structures/red_black_tree/red_black_tree.cpp
  ${PROJECT_SOURCE_DIR}/data_structures/avl_tree/avl_tree.cpp
)

foreach(exe ${EXECUTABLES})
  get_filename_component(FILE_NAME ${exe} NAME_WE)
  add_executable(${FILE_NAME} ${exe} ${PROJECT_SOURCE_DIR}/external/easyloggingpp/easylogging++.cc)
  target_include_directories(${FILE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/external)
endforeach()

add_clang_format_target(format)