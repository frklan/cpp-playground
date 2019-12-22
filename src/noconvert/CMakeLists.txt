cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(noconvert)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_CXX_CLANG_TIDY 
  clang-tidy;
  -header-filter="*.h";
  -checks=*,-*-magic-numbers,-*vararg,-hicpp-signed-bitwise,-*-default-arguments,-fuchsia*,-modernize-use-trailing-return-type;
)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

