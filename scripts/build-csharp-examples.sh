#!/bin/bash
# Build with CMake & Make (if possible)

echo "Building C/CMake Examples"
error_count=0
for dir in */; do
   dir_name=$(basename $dir)
   if [ -f "$dir_name/$dir_name.sln" ]; then
      echo "directory $dir" 
      pushd "$dir"
      xbuild
      error_count=$(($error_count + $?))
      popd
   else
      echo "Skipping $dir; not under cmake control"
   fi
done
exit $error_count
