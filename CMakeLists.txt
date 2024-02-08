cmake_minimum_required(VERSION 3.5)

project(OpSystemsCodeExamples)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_OPTIONAL_EXAMPLES "Build optional examples" OFF)

if(UNIX AND APPLE)
  message("--> We only provide limited Apple support at this time. Please use a Linux system if at all possible..")
  message("--> Some GNU-specific examples will be disabled.")
endif()

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

# cmake Windows issue: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(lwlog-lib)
add_subdirectory(lwlog-demo)
add_subdirectory(bsd-tree-lib)
add_subdirectory(bsd-tree-demo)
add_subdirectory(better_gets)
add_subdirectory(bounded-buffer)
add_subdirectory(c_intro)
add_subdirectory(dining-philosophers)
add_subdirectory(dir_list)
add_subdirectory(dir_list_cpp)
add_subdirectory(domain_sock)
add_subdirectory(file_rw)
add_subdirectory(fork)
add_subdirectory(fork_exec)
add_subdirectory(fork_pipe)
add_subdirectory(fork_sigchld)
add_subdirectory(fork_sigchld2)
add_subdirectory(getopt)
add_subdirectory(llnl_pthreads_examples)
add_subdirectory(malloc)
add_subdirectory(mmap)
add_subdirectory(mmap_locks)
add_subdirectory(objects)
add_subdirectory(parity)
add_subdirectory(qsort-demo)
add_subdirectory(read-write-demo)
add_subdirectory(regex-demo)
add_subdirectory(simple_adt)
add_subdirectory(rational_adt)
add_subdirectory(std-queue)
add_subdirectory(strbuffer_t)
add_subdirectory(strbuffer-demo)
add_subdirectory(strlen)
add_subdirectory(strtok)
add_subdirectory(syscall)
add_subdirectory(vectored_io)
add_subdirectory(wait)
add_subdirectory(hello-exe)
add_subdirectory(hello-lib)
add_subdirectory(charlist_t)


if(BUILD_OPTIONAL_EXAMPLES)

    if(UNIX AND NOT APPLE)
      add_subdirectory(monitor)
      add_subdirectory(mutex)
      add_subdirectory(semaphore)
      add_subdirectory(spin_lock)
      add_subdirectory(std-hsearch)
      add_subdirectory(std-tsearch)
      add_subdirectory(stm)
    else()
    endif()
endif()
