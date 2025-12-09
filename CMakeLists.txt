cmake_minimum_required(VERSION 3.20)

project(simplest_hello_world)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

if(NOT MSVC)
add_compile_options(
  -Wextra
  -Wall
  -Wformat
  -Wformat=2
  -Wimplicit-fallthrough
  -Wbidi-chars=any
  -pedantic
)

endif()

add_executable(hello_world
 main.cpp
 classes.cpp
 functions/functions.cpp
)

target_include_directories(hello_world
  PRIVATE
  ${PROJECT_SOURCE_DIR}/functions
)

target_include_directories(hello_world
  PRIVATE
  ${PROJECT_SOURCE_DIR}/headers
)
