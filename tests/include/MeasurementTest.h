#include "Measurement.h"
#include "gtest/gtest.h"

TEST(MeasurementTest, InitializationEmptyTest) {
  Measurement mes_test;
  EXPECT_EQ(mes_test.get_amount(), 0.0);
  EXPECT_EQ(mes_test.get_unit(), "");
}

TEST(MeasurementTest, InitializationTest) {
  double amount_truth = 100.0;
  string unit_truth = "g";

  Measurement mes_test;
  mes_test.set_amount(amount_truth);
  mes_test.set_unit(unit_truth);

  EXPECT_EQ(amount_truth, mes_test.get_amount()) << "Amount did not validate!";
  EXPECT_EQ(unit_truth, mes_test.get_unit()) << "Unit did not validate!";
}

// TEST(MeasurementTest, AddOperatorTest) {

// }

// TEST(MeasurementTest, SubtractOperatorTest) {

// }

// TEST(MeasurementTest, MultiplyOperatorTest) {

// }

// TEST(MeasurementTest, DivideOperatorTest) {

// }
