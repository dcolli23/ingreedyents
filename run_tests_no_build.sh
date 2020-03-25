#!/bin/bash

cd build
cmake -DRUN_TESTS=ON ..
make
./test_main