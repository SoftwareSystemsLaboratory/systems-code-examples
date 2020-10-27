project("pthreads")

cmake_minimum_required(VERSION 2.6)

# https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
# We only need 'bin' here.


# Just ignore this. Only needed when using GoogleTest.
if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(llnl1 llnl1.c)
target_link_libraries(llnl1 pthread)

add_executable(llnl2 llnl2.c)
target_link_libraries(llnl2 pthread)

add_executable(llnl_cv1 llnl_cv1.c)
target_link_libraries(llnl_cv1 pthread)

add_executable(llnl_cv1_tsd llnl_cv1_tsd.c)
target_link_libraries(llnl_cv1_tsd pthread)
