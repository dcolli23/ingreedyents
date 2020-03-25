#include "IngredientRequest.h"
#include "gtest/gtest.h"

const string UPC = "041631000564";

TEST(IngredientRequestTest, InitializationTest) {
  IngredientRequest* req = new IngredientRequest(UPC);
  delete req;
}

TEST(IngredientRequestTest, FormURLTest) {
  IngredientRequest* req = new IngredientRequest(UPC);
  req->form_URL();
  string URL_test = req->get_URL();
  string URL_truth = "https://api.spoonacular.com/food/products/upc/" + UPC 
    + "/information?";//apiKey=XXX";
  
  EXPECT_EQ(URL_test, URL_truth) << "URL did not form correctly!";

  delete req;
}