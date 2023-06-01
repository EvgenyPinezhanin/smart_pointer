cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME smart_pointer)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)

set(PROJECT_LIBRARY "${PROJECT_NAME}")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${PROJECT_INCLUDE}")

# BUILD
add_subdirectory(samples)

# REPORT
message(STATUS "")
message(STATUS "General configuration for ${PROJECT_NAME}")
message(STATUS "======================================")
message(STATUS "")
message(STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "")
