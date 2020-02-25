#include "ingredient_result.h"

IngredientResult::IngredientResult(string json_result_string) {
  body = json_result_string;
}

IngredientResult::~IngredientResult() {}

string IngredientResult::get_body() {
  return body;
}