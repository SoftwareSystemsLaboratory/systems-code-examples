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

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library

add_executable(hsearch-manpage-htable-demo hsearch-manpage-htable.c)
#target_compile_options(bsearch-manpage-htable-demo PRIVATE -Werror -Wall -Wextra)

add_executable(hsearch-better hsearch-better.c)
#target_compile_options(bsearch-better PRIVATE -Werror -Wall -Wextra)

