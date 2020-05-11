cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(ocp)


set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

unset(CMAKE_CXX_CLANG_TIDY )

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC version)

