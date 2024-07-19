cmake_minimum_required(VERSION 3.25)

project(DSA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(cmake/ClangFormat.cmake)

set(CMAKE_BUILD_TYPE Debug)

add_executable(red_black_tree
  ${PROJECT_SOURCE_DIR}/data_structures/red_black_tree/red_black_tree.cpp
  ${PROJECT_SOURCE_DIR}/external/easyloggingpp/easylogging++.cc
)

target_include_directories(red_black_tree PUBLIC
  ${PROJECT_SOURCE_DIR}/external
)

add_clang_format_target(format)