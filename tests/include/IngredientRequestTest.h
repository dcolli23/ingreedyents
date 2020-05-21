#include "IngredientRequest.h"
#include "gtest/gtest.h"

const string UPC = "041631000564";
const string API_KEY = "XXX"; // Fake API key for testing.

class IngredientRequestTest : public testing::Test {
  protected:
    IngredientRequest* my_request;

    // Set up the IngredientRequest during each test.
    void SetUp() override {
      my_request = new IngredientRequest(UPC, API_KEY);
    }

    void TearDown() override {
      delete my_request;
    };
};

TEST_F(IngredientRequestTest, FormFDCIDURLTest) {
  my_request->form_FDC_ID_URL();
  string URL_test = my_request->get_FDC_ID_URL();
  string URL_truth = "https://api.nal.usda.gov/fdc/v1/foods/search?query=" + UPC 
    + "&api_key=XXX";
  
  EXPECT_EQ(URL_test, URL_truth) << "URL did not form correctly!";
}

TEST_F(IngredientRequestTest, FormDetailedNutritionURLTest) {
  my_request->form_detailed_nutrition_URL();
  string URL_test = my_request->get_detailed_nutrition_URL();
  string URL_truth = "https://api.nal.usda.gov/fdc/v1/food/?api_key=XXX";
  EXPECT_EQ(URL_test, URL_truth) << "URL did not form correctly!";
}