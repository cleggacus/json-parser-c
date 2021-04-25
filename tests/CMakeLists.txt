cmake_minimum_required(VERSION 3.6)

project(json_parser_test C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(src/include)
file(GLOB SOURCES "src/*.c")

add_executable(json ${SOURCES})
target_link_libraries(json json_parser)