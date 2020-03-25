#include "IngredientResult.h"

IngredientResult::IngredientResult(string json_result_string) {
  body = json_result_string;
  ID = INVALID_INT;
  ingredient_name = INVALID_STRING;
  calories = INVALID_DOUBLE;
  carbs_grams = INVALID_INT;
  fat_grams = INVALID_INT;
  protein_grams = INVALID_INT;
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

//! Returns the calories of the ingredient per serving size
double IngredientResult::get_calories() { return calories; }

//! Returns the grams of carbs of the ingredient per serving size
int IngredientResult::get_carbs() { return carbs_grams; }

//! Returns the grams of fat of the ingredient per serving size
int IngredientResult::get_fat() { return fat_grams; }

//! Returns the grams of protein of the ingredient per serving size
int IngredientResult::get_protein() { return protein_grams; }

//! Parses `body` and stores parsed results as private members of this class 
void IngredientResult::parse_body() {
  string temp_str;
  rapidjson::Document doc;

  // Parse the JSON string into a DOM tree.
  rapidjson::ParseResult parse_ok = doc.Parse(body.c_str());

  try {
    if (!parse_ok) throw runtime_error("JSON did not parse correctly!");
  }
  catch (exception& e) {
    JSONErr::catch_fatal_exception(e);
  }

  // Store the ingredient ID.
  JSONErr::check_doc_member_int(doc, "id");
  ID = doc["id"].GetInt();

  // Store the ingredient name.
  JSONErr::check_doc_member_string(doc, "title");
  ingredient_name = doc["title"].GetString();

  // Store the macro information.
  JSONErr::check_doc_member_object(doc, "nutrition");
  const rapidjson::Value& nutrition = doc["nutrition"];
  JSONErr::check_doc_member_number(nutrition, "calories");
  calories = nutrition["calories"].GetDouble();
  JSONErr::check_doc_member_string(nutrition, "carbs");
  carbs_grams = get_macro_gram_amount(nutrition["carbs"].GetString());
  JSONErr::check_doc_member_string(nutrition, "fat");
  fat_grams = get_macro_gram_amount(nutrition["fat"].GetString());
  JSONErr::check_doc_member_string(nutrition, "protein");
  protein_grams = get_macro_gram_amount(nutrition["protein"].GetString());
}

//! Gets the macro gram amount from the macro's string
int IngredientResult::get_macro_gram_amount(string macro_str) {
  return stoi(macro_str.substr(0, macro_str.length() - 1));
}
