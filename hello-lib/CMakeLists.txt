add_library (hello-lib hello.c)

target_include_directories (hello-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
