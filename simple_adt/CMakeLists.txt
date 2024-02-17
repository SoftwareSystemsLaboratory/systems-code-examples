FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  point_demo2
  point_demo2.c
  point.c)

target_link_libraries(
  point_demo2
  -lm
)

add_executable(
  point_tests
  point_tests.cc
  point.c
)
 
target_link_libraries(
  point_tests
  gtest_main
  -lpthread
)


include(GoogleTest)
gtest_discover_tests(point_tests)
