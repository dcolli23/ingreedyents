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

// TEST_F(IngredientResultTest, TestCalorieParse) {
//   double calorie_truth = 30.0;
//   EXPECT_EQ(my_result->get_calories(), calorie_truth);
// }

// TEST_F(IngredientResultTest, TestCarbParse) {
//   int carb_truth = 8;
//   EXPECT_EQ(my_result->get_carbs(), carb_truth);
// }

// TEST_F(IngredientResultTest, TestFatParse) {
//   int fat_truth = 0;
//   EXPECT_EQ(my_result->get_fat(), fat_truth);
// }

// TEST_F(IngredientResultTest, TestProteinParse) {
//   int protein_truth = 0;
//   EXPECT_EQ(my_result->get_protein(), protein_truth);
// }

// TEST_F(IngredientResultTest, TestCalcium) {
//   float calcium_truth = 95.0;
//   // EXPECT_EQ(my_result->nutrients["Calcium, Ca"], calcium_truth);
// }