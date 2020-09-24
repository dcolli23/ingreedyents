#!/bin/bash

# No need to make the build directory if it's already there.
if [ -d build ]
then
  cd build
else
  mkdir build
  cd build
fi

# Delete the old test executable.
if [ -f test_main ]
then
  rm test_main
fi

cmake -DRUN_TESTS=ON ..
make

# Run the test suites.
if [ -f test_main ]
then
  ./test_main
else
  echo "Build failed!"
fi