#pragma once
#include "IngredientResult.h"
#include "HTTPSGETter.h"

#include <string>
using namespace std;

const string UPC_FORMATTER = "{UPC}";
const string BASE_URL = "https://api.spoonacular.com/food/products/upc/" + UPC_FORMATTER
  + "/information?";

class IngredientRequest {
public:
  IngredientRequest(string UPC, string API_key);
  ~IngredientRequest();

  // void set_UPC();

  string get_URL();


  void form_URL();
  

private:
  string API_key;
  string UPC;
  string URL;
  IngredientResult* result;
  HTTPSGETter* getter;
};