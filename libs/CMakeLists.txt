cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(version)

set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")
add_subdirectory(libfort)
