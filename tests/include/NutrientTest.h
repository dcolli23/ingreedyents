#pragma once
#include "Nutrient.h"
#include "JSONFuncs.h"

#include <uniTypes/uniTypes.h>
#include "gtest/gtest.h"

#include <fstream>

using namespace uniTypes::string_literals;

const string NUTRIENT_FILE = "../tests/data/example_nutrient.json";

class NutrientTest : public testing::Test {
  protected:
    Nutrient* my_nutrient;
    rapidjson::Document* p_doc;

    // Set up the nutrient class.
    void SetUp() override {
      // Read and parse the JSON file.
      p_doc = new rapidjson::Document();
      JSONFuncs::parse_json(NUTRIENT_FILE, *p_doc);

      my_nutrient = new Nutrient(*p_doc);
    }
    void TearDown() override {
      delete my_nutrient;
    }
};

TEST_F(NutrientTest, InitializationTest) {
  string name_truth = "Calcium, Ca";
  uniTypes::Mass serving_truth = 95.0_mg;
  uniTypes::Mass serving_test;

  string name_test = my_nutrient->get_name();
  serving_test = my_nutrient->get_serving();

  EXPECT_EQ(name_test, name_truth);
  EXPECT_FLOAT_EQ(serving_test.convertTo(uniTypes::milligram), 
    serving_truth.convertTo(uniTypes::milligram));
}

TEST_F(NutrientTest, SetServingTest) {
  uniTypes::Mass additional_amount = 10.0_g;
  uniTypes::Mass amount_truth = 105.0_g;
  
  uniTypes::Mass prev_mes = my_nutrient->get_serving();
  uniTypes::Mass new_serving = prev_mes + additional_amount;
  my_nutrient->set_serving(new_serving);

  EXPECT_FLOAT_EQ(amount_truth.convertTo(uniTypes::gram),
    my_nutrient->get_serving().convertTo(uniTypes::gram));
}

TEST_F(NutrientTest, SetNameTest) {
  string name_test = "this is a test name";
  my_nutrient->set_name(name_test);

  EXPECT_EQ(name_test, my_nutrient->get_name());
}