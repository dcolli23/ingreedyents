#!/bin/bash

rm -rf build
mkdir build && cd build
cmake -DBUILD_TESTS=OFF ..
make