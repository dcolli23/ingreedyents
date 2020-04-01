#include "Nutrient.h"
#include "gtest/gtest.h"

#include "JSONFuncs.h"

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

  string name_test = my_nutrient->get_name();
  double amount_test = my_nutrient->get_amount();
  string unit_test = my_nutrient->get_unit();

  EXPECT_EQ(name_test, name_truth);
  EXPECT_EQ(amount_test, amount_truth);
  EXPECT_EQ(unit_test, unit_truth);
}