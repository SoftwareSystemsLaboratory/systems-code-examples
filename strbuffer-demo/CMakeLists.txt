add_executable(strbuffer_demo strbuffer_demo.c)

add_executable(strbuffer_getline_demo strbuffer_getline_demo.c)

target_link_libraries (strbuffer_demo LINK_PUBLIC strbuffer-lib)

target_link_libraries (strbuffer_getline_demo LINK_PUBLIC strbuffer-lib)
