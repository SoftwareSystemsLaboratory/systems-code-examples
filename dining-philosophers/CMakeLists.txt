add_executable(diner-demo diner-demo.c diners.h diners.c millisleep.h millisleep.c)
target_link_libraries(diner-demo pthread)

