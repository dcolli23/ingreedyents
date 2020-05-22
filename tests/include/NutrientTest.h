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
  EXPECT_EQ(serving_test.get_amount(), amount_truth);
  EXPECT_EQ(serving_test.get_unit(), unit_truth);
}

TEST_F(NutrientTest, SetServingTest) {
  double additional_amount = 10.0;
  double amount_truth = 105.0;
  string unit = "mg";
  Measurement new_mes;
  new_mes.set_amount(additional_amount);
  new_mes.set_unit(unit);

  Measurement prev_mes = my_nutrient->get_serving();
  my_nutrient->set_serving(prev_mes + new_mes);

  EXPECT_EQ(amount_truth, my_nutrient->get_serving().get_amount());
  EXPECT_EQ(unit, my_nutrient->get_serving().get_unit());
}

TEST_F(NutrientTest, SetNameTest) {

}