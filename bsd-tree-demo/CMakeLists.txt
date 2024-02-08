add_executable (int-tree-demo int-tree-main.c int-tree.c)

target_link_libraries (int-tree-demo LINK_PUBLIC bsd-tree-lib)
