#include "Measurement.h"
#include "gtest/gtest.h"

TEST(MeasurementTest, InitializationEmptyTest) {
  Measurement mes_test;
  EXPECT_EQ(mes_test.get_amount(), 0.0);
  EXPECT_EQ(mes_test.get_unit(), "");
}

TEST(MeasurementTest, InitializationManaulTest) {
  double amount_truth = 100.0;
  string unit_truth = "g";

  Measurement mes_test;
  mes_test.set_amount(amount_truth);
  mes_test.set_unit(unit_truth);

  EXPECT_EQ(amount_truth, mes_test.get_amount()) << "Amount did not validate!";
  EXPECT_EQ(unit_truth, mes_test.get_unit()) << "Unit did not validate!";
}

TEST(MeasurementTest, InitializationTest) {
  double amount_truth = 34.89;
  string unit_truth = "ml";

  Measurement mes_test = Measurement(amount_truth, unit_truth);

  EXPECT_EQ(amount_truth, mes_test.get_amount()) << "Amount did not validate!";
  EXPECT_EQ(unit_truth, mes_test.get_unit()) << "Unit did not validate!";
}

TEST(MeasurementTest, AddOperatorTest) {
  Measurement res_truth;
  Measurement res_test, m1, m2;

  res_truth.set_amount(10.0);
  res_truth.set_unit("g");

  m1.set_amount(7.0);
  m1.set_unit("g");
  m2.set_amount(3.0);
  m2.set_unit("g");

  res_test = m1 + m2;

  EXPECT_EQ(res_test.get_amount(), res_truth.get_amount());
  EXPECT_EQ(res_test.get_unit(), res_truth.get_unit());
}

TEST(MeasurementTest, SubtractOperatorTest) {
  Measurement res_truth;
  Measurement res_test, m1, m2;

  res_truth.set_amount(3.0);
  res_truth.set_unit("g");

  m1.set_amount(15.0);
  m1.set_unit("g");
  m2.set_amount(12.0);
  m2.set_unit("g");

  res_test = m1 - m2;

  EXPECT_EQ(res_test.get_amount(), res_truth.get_amount());
  EXPECT_EQ(res_test.get_unit(), res_truth.get_unit());
}

// TEST(MeasurementTest, SubtractOperatorTestFail) {
//   Measurement res_test, m1, m2;

//   m1.set_amount(15.0);
//   m1.set_unit("g");
//   m2.set_amount(12.0);
//   m2.set_unit("g");

//   EXPECT_DEATH(res_test = m1 - m2);
// }

TEST(MeasurementTest, MultiplyOperatorTest) {
  Measurement res_truth;
  Measurement res_test, m1;

  res_truth.set_amount(10.0);
  res_truth.set_unit("mg");

  m1.set_amount(5.0);
  m1.set_unit("mg");

  res_test = m1 * 2;

  EXPECT_EQ(res_test.get_amount(), res_truth.get_amount());
  EXPECT_EQ(res_test.get_unit(), res_truth.get_unit());
}

TEST(MeasurementTest, DivideOperatorTest) {
  Measurement res_truth;
  Measurement res_test, m1;

  res_truth.set_amount(10.0);
  res_truth.set_unit("kg");

  m1.set_amount(30.0);
  m1.set_unit("kg");

  res_test = m1 / 3.0;

  EXPECT_EQ(res_test.get_amount(), res_truth.get_amount());
  EXPECT_EQ(res_test.get_unit(), res_truth.get_unit());
}

TEST(MeasurementTest, PlusEqualsOperatorTest) {
  Measurement res_truth;
  Measurement res_test, m2;

  res_truth.set_amount(70.0);
  res_truth.set_unit("kg");

  res_test.set_amount(30.0);
  res_test.set_unit("kg");
  m2.set_amount(40.0);
  m2.set_unit("kg");

  res_test += m2;

  EXPECT_EQ(res_test.get_amount(), res_truth.get_amount());
  EXPECT_EQ(res_test.get_unit(), res_truth.get_unit());
}

TEST(MeasurementTest, MinusEqualsOperatorTest) {
  Measurement res_truth;
  Measurement res_test, m2;

  res_truth.set_amount(10.0);
  res_truth.set_unit("kg");

  res_test.set_amount(40.0);
  res_test.set_unit("kg");
  m2.set_amount(30.0);
  m2.set_unit("kg");

  res_test -= m2;

  EXPECT_EQ(res_test.get_amount(), res_truth.get_amount());
  EXPECT_EQ(res_test.get_unit(), res_truth.get_unit());
}

// TEST(MeasurementTest, MinusEqualsOperatorTestFail) {
//   Measurement m1, m2;

//   m1.set_amount(30.0);
//   m1.set_unit("kg");
//   m2.set_amount(40.0);
//   m2.set_unit("kg");

//   EXPECT_DEATH(m1 -= m2);
// }