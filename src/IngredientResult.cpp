#include "IngredientResult.h"

IngredientResult::IngredientResult(string json_result_string) {
  body = json_result_string;
  ID = INVALID_INT;
  ingredient_name = INVALID_STRING;
  // calories = INVALID_DOUBLE;
  // carbs_grams = INVALID_INT;
  // fat_grams = INVALID_INT;
  // protein_grams = INVALID_INT;
  parse_body();
}

IngredientResult::~IngredientResult() {}

//! Sets the body of the HTTPS GET request result
void IngredientResult::set_body(string body) { this->body = body; }

//! Returns the unparsed `body` of the HTTPS GET request as a string
string IngredientResult::get_body() { return body; }

//! Returns the ID for this ingredient
int IngredientResult::get_ID() { return ID; }

//! Returns the name of the ingredient
string IngredientResult::get_ingredient_name() { return ingredient_name; }

//! Returns the serving size
Measurement IngredientResult::get_serving_size() { return serving_size; }

//! Parses `body` and stores parsed results as private members of this class 
void IngredientResult::parse_body() {
  string nut_name;
  rapidjson::Document doc;
  Nutrient* nut;

  // Parse the JSON string into a DOM tree.
  rapidjson::ParseResult parse_ok = doc.Parse(body.c_str());

  try {
    if (!parse_ok) throw runtime_error("JSON did not parse correctly!");
  }
  catch (exception& e) {
    JSONFuncs::catch_fatal_exception(e);
  }

  // Populate the nutrients map from our array of nutrients.
  JSONFuncs::check_doc_member_array(doc, "foodNutrients");
  rapidjson::Value& foodNutrients = doc["foodNutrients"];
  for (rapidjson::Value& v : foodNutrients.GetArray()) {
    JSONFuncs::check_doc_member_object(v, "nutrient");
    JSONFuncs::check_doc_member_string(v["nutrient"], "name");
    nutrients[v["nutrient"]["name"].GetString()] = new Nutrient(v);
  }

  // Store the ingredient ID.
  JSONFuncs::check_doc_member_int(doc, "fdcId");
  ID = doc["fdcId"].GetInt();

  // Store the ingredient name.
  JSONFuncs::check_doc_member_string(doc, "description");
  ingredient_name = doc["description"].GetString();

  // Store the serving size and unit.
  JSONFuncs::check_doc_member_number(doc, "servingSize");
  serving_size.set_amount(doc["servingSize"].GetDouble());

  JSONFuncs::check_doc_member_string(doc, "servingSizeUnit");
  serving_size.set_unit(doc["servingSizeUnit"].GetString());
}

//! Gets the macro gram amount from the macro's string
int IngredientResult::get_macro_gram_amount(string macro_str) {
  return stoi(macro_str.substr(0, macro_str.length() - 1));
}
