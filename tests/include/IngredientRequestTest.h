#include "IngredientRequest.h"
#include "gtest/gtest.h"

const string UPC = "041631000564";
const string API_KEY = "XXX"; // Fake API key for testing.

class IngredientRequestTest : public testing::Test {
  protected:
    IngredientRequest* my_result;

    // Set up the IngredientRequest during each test.
    void SetUp() override {
      my_result = new IngredientRequest(UPC, API_KEY);
    }

    void TearDown() override {
      delete my_result;
    };
};

TEST_F(IngredientRequestTest, FormURLTest) {
  my_result->form_URL();
  string URL_test = my_result->get_URL();
  string URL_truth = "https://api.spoonacular.com/food/products/upc/" + UPC 
    + "?apiKey=XXX";
  
  EXPECT_EQ(URL_test, URL_truth) << "URL did not form correctly!";
}