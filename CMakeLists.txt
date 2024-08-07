cmake_minimum_required(VERSION 3.25)

project(DSA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(cmake/ClangFormat.cmake)

set(CMAKE_BUILD_TYPE Debug)

set(EXCLUDED_DIRS "build")

file(GLOB_RECURSE ALL_CPP_FILES
  ${PROJECT_SOURCE_DIR}/*.cpp
)

set(FILTERED_CPP_FILES)
foreach(FILE ${ALL_CPP_FILES})
  set(EXCLUDE_FILE FALSE)
  foreach(EXCLUDED_DIR ${EXCLUDED_DIRS})
    if(${FILE} MATCHES ${EXCLUDED_DIR})
      set(EXCLUDE_FILE TRUE)
      break()
    endif()
  endforeach()
  if(NOT EXCLUDE_FILE)
    list(APPEND FILTERED_CPP_FILES ${FILE})
  endif()
endforeach()


set(EXECUTABLES ${FILTERED_CPP_FILES})

foreach(exe ${EXECUTABLES})
  get_filename_component(FILE_NAME ${exe} NAME_WE)
  add_executable(${FILE_NAME} ${exe})
endforeach()

add_clang_format_target(format)