add_executable (lwlog-demo lwlog-demo.c)



# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (lwlog-demo LINK_PUBLIC lwlog-lib)
