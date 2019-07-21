cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ncscpp)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(ncscpp_lib)

file(GLOB SOURCE_FILES *.cpp)

# The main program
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ncscpp_lib)

target_link_libraries(${PROJECT_NAME} PRIVATE version)
