#!/bin/bash

# Using GoogleTest is best by fetching from Google and doing a local build
git clone https://github.com/google/googletest
mkdir -p googletest/build
pushd googletest/build
cmake ..
sudo make install
popd

