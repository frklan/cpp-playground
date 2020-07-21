cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(_template)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(_template_lib)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE _template_lib)
