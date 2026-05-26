add_library (
    charlist-lib
    charlist.c)

target_include_directories (
    charlist-lib 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTING)
    add_executable(
        charlist_tests
        charlist_tests.cc
        charlist.c
    )

    target_link_libraries(
        charlist_tests
        gtest_main
        -lpthread)

    include(GoogleTest)
    gtest_discover_tests(charlist_tests)
endif()
