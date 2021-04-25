cmake_minimum_required(VERSION 3.6)

project(json_parser C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(src/include)
file(GLOB SOURCES "src/*.c")
file(GLOB INCLUDE "src/include/*.h")
add_library(json_parser STATIC ${SOURCES})

install(TARGETS json_parser DESTINATION lib)
install(FILES ${INCLUDE} DESTINATION include/json_parser)