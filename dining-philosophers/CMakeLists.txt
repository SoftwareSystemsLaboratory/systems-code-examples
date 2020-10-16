project("diners")

cmake_minimum_required(VERSION 2.6)

# Just ignore this. Only needed when using GoogleTest.
if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(diner-demo diner-demo.c diners.h diners.c millisleep.h millisleep.c)
target_link_libraries(diner-demo pthread)

