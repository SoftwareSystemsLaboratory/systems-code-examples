FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        rational_demo
        rational_demo.c
        rational.c)

target_link_libraries(
        rational_demo
        lwlog-lib
        -lm
)

add_executable(
        rational_tests
        rational_tests.cc
        rational.c
)

target_link_libraries(
        rational_tests
        gtest_main
        lwlog-lib
        -lpthread
)

include(GoogleTest)
gtest_discover_tests(rational_tests)
