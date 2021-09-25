add_executable(semaphore-demo debug.cc main.cc mutex.cc queue.cc semaphore.cc)
target_link_libraries(semaphore-demo -lpthread)
