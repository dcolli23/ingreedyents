#pragma once
#include "gtest/gtest.h"
#include "Ingredient.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace uniTypes::string_literals;

const std::string JSON_RESULT_LOCATION = "../tests/data/ingredient_nutrition_get_result.json";

class IngredientResultTest : public testing::Test {
  protected:
    Ingredient* my_result;

    // Set up the IngredientResult during each test.
    void SetUp() override {
      // Read in the JSON result file as a string.
      std::ifstream fin;

      // Initialize the new IngredientResult.
      fin.open(JSON_RESULT_LOCATION);
      if (fin.fail()) {
        cout << "File failed to open!" << endl;
      }
      my_result = new Ingredient(fin);
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
  double test_amount, truth_amount;
  uniTypes::Mass mes_truth = 42.0_g;

  uniTypes::Mass mes_test = my_result->get_serving_size();

  test_amount = mes_test.convertTo(uniTypes::gram);
  truth_amount = mes_truth.convertTo(uniTypes::gram);
  EXPECT_FLOAT_EQ(mes_test, mes_truth);
}

TEST_F(IngredientResultTest, TestCalcium) {
  double test_amount, truth_amount;
  uniTypes::Mass serving_truth = 95.0_mg;

  uniTypes::Mass serving_test = my_result->nutrients["Calcium, Ca"]->get_serving();
  
  test_amount = serving_test.convertTo(uniTypes::gram);
  truth_amount = serving_truth.convertTo(uniTypes::gram);
  EXPECT_FLOAT_EQ(test_amount, truth_amount);
}

TEST_F(IngredientResultTest, TestIron) {
  double test_amount, truth_amount;
  uniTypes::Mass serving_truth = 0.860_mg;

  uniTypes::Mass serving_test = my_result->nutrients["Iron, Fe"]->get_serving();
  
  test_amount = serving_test.convertTo(uniTypes::gram);
  truth_amount = serving_truth.convertTo(uniTypes::gram);
  EXPECT_FLOAT_EQ(test_amount, truth_amount);
}

TEST_F(IngredientResultTest, TestVitaminA) {
  double test_amount, truth_amount;
  uniTypes::UOBA serving_truth = 238.0_IU;

  uniTypes::UOBA serving_test = my_result->nutrients["Vitamin A, IU"]->get_serving();
  
  test_amount = serving_test.convertTo(uniTypes::IU);
  truth_amount = serving_truth.convertTo(uniTypes::IU);
  EXPECT_FLOAT_EQ(test_amount, truth_amount);
}

TEST_F(IngredientResultTest, TestVitaminC) {
  double test_amount, truth_amount;
  uniTypes::Mass serving_truth = 2.90_mg;

  uniTypes::Mass serving_test = my_result->nutrients["Vitamin C, total ascorbic acid"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestThiamin) {
  double test_amount, truth_amount;
  double amount_truth = 0E-8;
  string unit_truth = "mg";

  uniTypes::Mass serving_test = my_result->nutrients["Thiamin"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestRiboflavin) {
  double test_amount, truth_amount;
  double amount_truth = 0.0810;
  string unit_truth = "mg";

  uniTypes::Mass serving_test = my_result->nutrients["Riboflavin"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestNiacin) {
  double test_amount, truth_amount;
  double amount_truth = 2.8570;
  string unit_truth = "mg";

  uniTypes::Mass serving_test = my_result->nutrients["Niacin"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestProtein) {
  double test_amount, truth_amount;
  double amount_truth = 9.520;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Protein"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestFat) {
  double test_amount, truth_amount;
  double amount_truth = 26.190;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Total lipid (fat)"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestCarbs) {
  double test_amount, truth_amount;
  double amount_truth = 61.90;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Carbohydrate, by difference"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestEnergy) {
  double test_amount, truth_amount;
  double amount_truth = 524.0;
  string unit_truth = "kcal";

  uniTypes::Mass serving_test = my_result->nutrients["Energy"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestSugars) {
  double test_amount, truth_amount;
  double amount_truth = 52.380;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Sugars, total including NLEA"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestFiber) {
  double test_amount, truth_amount;
  double amount_truth = 2.40;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Fiber, total dietary"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestSodium) {
  double test_amount, truth_amount;
  double amount_truth = 48.0;
  string unit_truth = "mg";

  uniTypes::Mass serving_test = my_result->nutrients["Sodium, Na"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestCholesterol) {
  double test_amount, truth_amount;
  double amount_truth = 12.0;
  string unit_truth = "mg";

  uniTypes::Mass serving_test = my_result->nutrients["Cholesterol"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestFattyAcidsTrans) {
  double test_amount, truth_amount;
  double amount_truth = 0E-8;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Fatty acids, total trans"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}

TEST_F(IngredientResultTest, TestFattyAcidsSaturated) {
  double test_amount, truth_amount;
  double amount_truth = 10.710;
  string unit_truth = "g";

  uniTypes::Mass serving_test = my_result->nutrients["Fatty acids, total saturated"]->get_serving();
  
  EXPECT_FLOAT_EQ(amount_truth, serving_test.get_amount());
}
