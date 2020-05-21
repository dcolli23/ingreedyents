#pragma once
#include "gtest/gtest.h"
#include "IngredientResult.h"
#include "Measurement.h"
#include <string>
#include <fstream>
#include <iostream>

const std::string JSON_RESULT_LOCATION = "../tests/data/ingredient_nutrition_get_result.json";

class IngredientResultTest : public testing::Test {
  protected:
    IngredientResult* my_result;

    // Set up the IngredientResult during each test.
    void SetUp() override {
      // Read in the JSON result file as a string.
      std::ifstream fin(JSON_RESULT_LOCATION);
      std::string json_str;
      
      fin.seekg(0, std::ios::end);
      json_str.reserve(fin.tellg());
      fin.seekg(0, std::ios::beg);

      json_str.assign((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
      
      // Initialize the new IngredientResult.
      my_result = new IngredientResult(json_str);
      my_result->parse_body();      
    }
    void TearDown() override {}
};

TEST_F(IngredientResultTest, TestIDParse) {
  int ID_truth = 541628;
  EXPECT_EQ(my_result->get_ID(), ID_truth);
}

TEST_F(IngredientResultTest, TestNameParse) {
  string name_truth = "M&M'S, PEANUT CHOCOLATE CANDIES";
  EXPECT_EQ(my_result->get_ingredient_name(), name_truth);
}

TEST_F(IngredientResultTest, TestServingSizeParse) {
  struct Measurement mes_truth;
  mes_truth.amount = 42.0;
  mes_truth.unit = "g";

  Measurement mes_test = my_result->get_serving_size();

  EXPECT_EQ(mes_test.amount, mes_truth.amount);
  EXPECT_EQ(mes_test.unit, mes_truth.unit);
}

TEST_F(IngredientResultTest, TestCalcium) {
  double amount_truth = 95.0;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Calcium, Ca"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestIron) {
  double amount_truth = 0.860;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Iron, Fe"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestVitaminA) {
  double amount_truth = 238.0;
  string unit_truth = "IU";

  Measurement serving_test = my_result->nutrients["Vitamin A, IU"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestVitaminC) {
  double amount_truth = 2.90;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Vitamin C, total ascorbic acid"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestThiamin) {
  double amount_truth = 0E-8;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Thiamin"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestRiboflavin) {
  double amount_truth = 0.0810;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Riboflavin"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestNiacin) {
  double amount_truth = 2.8570;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Niacin"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestProtein) {
  double amount_truth = 9.520;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Protein"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestFat) {
  double amount_truth = 26.190;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Total lipid (fat)"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestCarbs) {
  double amount_truth = 61.90;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Carbohydrate, by difference"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestEnergy) {
  double amount_truth = 524.0;
  string unit_truth = "kcal";

  Measurement serving_test = my_result->nutrients["Energy"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestSugars) {
  double amount_truth = 52.380;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Sugars, total including NLEA"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestFiber) {
  double amount_truth = 2.40;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Fiber, total dietary"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestSodium) {
  double amount_truth = 48.0;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Sodium, Na"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestCholesterol) {
  double amount_truth = 12.0;
  string unit_truth = "mg";

  Measurement serving_test = my_result->nutrients["Cholesterol"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestFattyAcidsTrans) {
  double amount_truth = 0E-8;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Fatty acids, total trans"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}

TEST_F(IngredientResultTest, TestFattyAcidsSaturated) {
  double amount_truth = 10.710;
  string unit_truth = "g";

  Measurement serving_test = my_result->nutrients["Fatty acids, total saturated"]->get_serving();
  
  EXPECT_EQ(amount_truth, serving_test.amount);
  EXPECT_EQ(unit_truth, serving_test.unit);
}
