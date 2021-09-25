add_executable(lock-demo main.c lock.c)
target_link_libraries(lock-demo -lpthread)
