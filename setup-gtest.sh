#!/bin/bash

git clone https://github.com/google/googletest.git
pushd googletest
cmake .
make
sudo make install
popd
rm -rf googletest

