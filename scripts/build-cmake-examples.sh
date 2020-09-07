#!/bin/bash

# Build with CMake & Make (if possible)

echo "Building C/CMake Examples"
error_count=0
for dir in */; do
   if [ -f "$dir/CMakeLists.txt" ]; then
      echo "directory $dir" 
      pushd "$dir"
      rm -f CMakeCache.txt Makefile
      cmake .
      error_count=$(($error_count + $?))
      make
      error_count=$(($error_count + $?))
      popd
   else
      echo "Skipping $dir; not under cmake control"
   fi
done
exit $error_count
