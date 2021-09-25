add_executable(stm-demo main.cc mutex.cc trans.cc)
target_link_libraries(stm-demo -lpthread)
