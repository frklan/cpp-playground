cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_DIR source)
file(GLOB SOURCE_FILES *.cpp)

foreach(CPP_FILE ${SOURCE_FILES})
  get_filename_component(SOURCE_BASENAME ${CPP_FILE} NAME)
  string (REPLACE ".cpp" "" EXE_NAME ${SOURCE_BASENAME})
  add_executable(${EXE_NAME} ${CPP_FILE})
endforeach(CPP_FILE ${SOURCE_FILES})


# Build each subdir as separeate "project"
FILE(GLOB children *)
FOREACH(child ${children})
  IF(IS_DIRECTORY ${curdir}/${child})
    ADD_SUBDIRECTORY(${child})
  ENDIF()
ENDFOREACH()
