find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(point_demo point_demo.c point.c)
target_link_libraries(point_demo -lm)

add_executable(point_demo2 point_demo2.c point.c)
target_link_libraries(point_demo2 -lm)

add_executable(point_tests point_tests.cc point.c)
target_link_libraries(point_tests ${GTEST_LIBRARIES} -lpthread)
