cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(switch)

#add_subdirectory(${PROJECT_NAME}_lib)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_CLANG_TIDY 
  clang-tidy;
  -header-filter="*.h";
  -checks=-cppcoreguidelines-pro-bounds-pointer-arithmetic,-clang-diagnostic-gnu-case-range;
)

add_compile_options(-Wno-gnu-case-range)



file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

target_link_libraries(${PROJECT_NAME} PUBLIC version)
