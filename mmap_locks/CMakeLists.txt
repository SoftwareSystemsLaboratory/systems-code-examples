add_executable(mmap-locks-producer producer.cc message.cc)
target_link_libraries(mmap-locks-producer -lpthread)

add_executable(mmap-locks-consumer consumer.cc message.cc)
target_link_libraries(mmap-locks-consumer -lpthread)
