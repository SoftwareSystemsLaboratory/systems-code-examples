add_executable(bounded-buffer bounded-buffer.c bbuffer.c bbuffer.h bboptions.c bboptions.h millisleep.c millisleep.h)
target_link_libraries(bounded-buffer pthread lwlog-lib)

