#!/bin/bash

cd build
cmake -DBUILD_TESTS=OFF ..
make
