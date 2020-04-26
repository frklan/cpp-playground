cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCE_FILES *.cpp)
foreach(CPP_FILE ${SOURCE_FILES})
  get_filename_component(SOURCE_BASENAME ${CPP_FILE} NAME)
  string (REPLACE ".cpp" "" EXE_NAME ${SOURCE_BASENAME})
  project(${EXE_NAME})
  add_executable(${PROJECT_NAME} ${CPP_FILE})
endforeach(CPP_FILE ${SOURCE_FILES})

