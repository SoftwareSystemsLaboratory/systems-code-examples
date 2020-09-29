project(HASHTABLE_DEMOS)
cmake_minimum_required(VERSION 2.6)

if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(UNIX AND NOT APPLE)
  message(">> Linux")
  add_compile_options(-DWITH_LINUX)
else()
  message(">> non-Linux")
  add_compile_options(-DWITH_APPLE) 
endif()


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(tsearch-manpage-tree tsearch-manpage-tree.c)

add_executable(tsearch-wordinfo-demo tsearch-wordinfo-demo.c)
