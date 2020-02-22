#include "gtest/gtest.h"
#include "example.h"

TEST(TestFunc, FirstTest) {
  example* my_examp = new example();
  EXPECT_EQ (0.0, my_examp->test_func(0.0));
}

int main (int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}