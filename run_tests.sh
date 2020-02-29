#!/bin/bash

rm -rf build
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
./test_main