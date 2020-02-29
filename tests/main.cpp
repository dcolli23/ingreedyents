#include "gtest/gtest.h"

// All of the test files we want to run.
#include "IngredientResultTest.h"
#include "CURLTest.h"
#include "HTTPSGETterTest.h"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}