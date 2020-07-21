cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cpp-playground)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_CLANG_TIDY 
  clang-tidy;
  -header-filter="*.h";
  -checks=*,-*vararg,-hicpp-signed-bitwise,-*-default-arguments,-fuchsia*,-modernize-use-trailing-return-type,-readability-convert-member-functions-to-static;
)

add_compile_options(
  -g
  -Weverything 
  -Wno-c++98-compat 
  -Wno-c++98-compat-pedantic
  -Wno-padded
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(test)
