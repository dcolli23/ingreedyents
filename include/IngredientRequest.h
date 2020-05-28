#pragma once
#include "Ingredient.h"
#include "HTTPSGETter.h"

#include <string>
using namespace std;

const string UPC_FORMATTER = "{UPC}";
const string FDC_ID_BASE_URL = "https://api.nal.usda.gov/fdc/v1/foods/search?query=" + UPC_FORMATTER;
const string DETAILED_NUTRITION_BASE_URL = "https://api.nal.usda.gov/fdc/v1/food/";

class IngredientRequest {
public:
  IngredientRequest(string UPC, string API_key);
  ~IngredientRequest();

  Ingredient* make_request();

  string get_FDC_ID_URL();
  string get_detailed_nutrition_URL();

  void form_FDC_ID_URL();
  void form_detailed_nutrition_URL();
  

private:
  string API_key;
  string UPC;
  string FDC_ID_URL;
  string FDC_ID;
  string detailed_nutrition_URL;
  Ingredient* result;
  HTTPSGETter* getter;
};