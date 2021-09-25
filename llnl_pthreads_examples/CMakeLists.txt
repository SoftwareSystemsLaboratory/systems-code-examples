add_executable(llnl1 llnl1.c)
target_link_libraries(llnl1 pthread)

add_executable(llnl2 llnl2.c)
target_link_libraries(llnl2 pthread)

add_executable(llnl_cv1 llnl_cv1.c)
target_link_libraries(llnl_cv1 pthread)

add_executable(llnl_cv1_tsd llnl_cv1_tsd.c)
target_link_libraries(llnl_cv1_tsd pthread)
