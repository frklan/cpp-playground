cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

message(STATUS "Cloning nanogui [Please wait]")
include(FetchContent)
FetchContent_Declare(nanogui
  GIT_REPOSITORY https://github.com/wjakob/nanogui.git
  GIT_TAG 7c9cfd360af9d92937b1ea86c8d24f2235efde08
  GIT_PROGRESS YES
)

FetchContent_GetProperties(nanogui)
if(NOT nanogui_POPULATED)
  FetchContent_Populate(nanogui)

  add_subdirectory(${nanogui_SOURCE_DIR} ${nanogui_BINARY_DIR})

  # nanogui spits out quite a lot of warnings wiith our settings, so disable them..
  add_compile_options(-Wno-everything)
  unset(CMAKE_CXX_CLANG_TIDY)
  set (CMAKE_CXX_STANDARD 11)
  
  set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
  set(NANOGUI_BUILD_PYTHON OFF CACHE BOOL " " FORCE)
  set(NANOGUI_INSTALL OFF CACHE BOOL " " FORCE)
  
  include_directories(${NANOGUI_EXTRA_INCS})
  target_include_directories(nanogui PUBLIC ${nanogui_SOURCE_DIR}/include)
endif()
