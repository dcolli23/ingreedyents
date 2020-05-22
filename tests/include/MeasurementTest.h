#include "Measurement.h"
#include "gtest/gtest.h"

TEST(MeasurementTest, InitializationEmptyTest) {
  struct Measurement mes_test;
  EXPECT_EQ(mes_test.amount, 0.0);
  EXPECT_EQ(mes_test.unit, "");
}

TEST(MeasurementTest, InitializationTest) {
  double amount_truth = 100.0;
  string unit_truth = "g";

  struct Measurement mes_test;
  mes_test.amount = amount_truth;
  mes_test.unit = unit_truth;

  EXPECT_EQ(amount_truth, mes_test.amount) << "Amount did not validate!";
  EXPECT_EQ(unit_truth, mes_test.unit) << "Unit did not validate!";
}