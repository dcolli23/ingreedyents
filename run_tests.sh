#!/bin/bash

rm -rf build
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
./ingredient_result_test