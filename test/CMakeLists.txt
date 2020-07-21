cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS OFF)

find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
foreach(SOURCE ${SOURCE_FILES})
  get_filename_component(SOURCE_FILE ${SOURCE} NAME)

  string(REPLACE ".cpp" "" SOURCE_FILE ${SOURCE_FILE})
  project(${SOURCE_FILE})
  add_executable(${PROJECT_NAME} ${SOURCE})
  target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
endforeach(SOURCE)

