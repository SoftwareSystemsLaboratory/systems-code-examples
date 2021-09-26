#!/bin/bash

# This script is used to setup GoogleTest in GitHub Actions.
# Unless you have a good reason to  run it, don't! :-)

git clone https://github.com/google/googletest.git
pushd googletest
cmake .
make
sudo make install
popd
rm -rf googletest

