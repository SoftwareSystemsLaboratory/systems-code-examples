add_executable(monitor-demo main.cc debug.cc monitor.cc mutex.cc queue.cc)
target_link_libraries(monitor-demo -lpthread)
