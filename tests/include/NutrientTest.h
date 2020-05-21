#include "Nutrient.h"
#include "JSONFuncs.h"
#include "Measurement.h"

#include "gtest/gtest.h"


#include <fstream>

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
  double amount_truth = 95.00000000;
  string unit_truth = "mg";
  Measurement serving_test;

  string name_test = my_nutrient->get_name();
  serving_test = my_nutrient->get_serving();

  EXPECT_EQ(name_test, name_truth);
  EXPECT_EQ(serving_test.amount, amount_truth);
  EXPECT_EQ(serving_test.unit, unit_truth);
}