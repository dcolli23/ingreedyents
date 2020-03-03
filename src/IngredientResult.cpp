#include "IngredientResult.h"
#include <iostream>

// Forward declarations for error handling functions.
void catch_fatal_exception(exception& e);
bool check_doc_has_member(const rapidjson::Value& doc, const char mem_name[], string& e_string);
bool check_doc_valid_array_index(const rapidjson::Value& doc, const char mem_name[], 
                                 rapidjson::SizeType ind, string& e_string);
void check_doc_member_object(const rapidjson::Value& doc, const char mem_name[]);
void check_doc_member_number(const rapidjson::Value& doc, const char mem_name[]);
void check_doc_member_number(const rapidjson::Value& doc, const char mem_name[],
                              rapidjson::SizeType ind);
void check_doc_member_int(const rapidjson::Value& doc, const char mem_name[]);
void check_doc_member_array(const rapidjson::Value& doc, const char mem_name[]);
void check_doc_member_string(const rapidjson::Value& doc, const char mem_name[]);
void check_doc_member_string(const rapidjson::Value& doc, const char mem_name[],
                              rapidjson::SizeType ind);

IngredientResult::IngredientResult(string json_result_string) {
  body = json_result_string;
}

IngredientResult::~IngredientResult() {}

//! Sets the body of the HTTPS GET request result
void IngredientResult::set_body(string body) { this->body = body; }

//! Returns the unparsed `body` of the HTTPS GET request as a string
string IngredientResult::get_body() { return body; }

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
    catch_fatal_exception(e);
  }

  // Store the ingredient ID.
  check_doc_member_int(doc, "id");
  ID = doc["id"].GetInt();

  // Store the ingredient name.
  check_doc_member_string(doc, "title");
  ingredient_name = doc["title"].GetString();

  // Store the macro information.
  check_doc_member_object(doc, "nutrition");
  const rapidjson::Value& nutrition = doc["nutrition"];
  check_doc_member_number(nutrition, "calories");
  calories = nutrition["calories"].GetDouble();
  check_doc_member_string(nutrition, "carbs");
  carbs_grams = get_macro_gram_amount(nutrition["carbs"].GetString());
  check_doc_member_string(nutrition, "fat");
  fat_grams = get_macro_gram_amount(nutrition["fat"].GetString());
  check_doc_member_string(nutrition, "protein");
  protein_grams = get_macro_gram_amount(nutrition["protein"].GetString());
}

//! Gets the macro gram amount from the macro's string
int IngredientResult::get_macro_gram_amount(string macro_str) {
  return stoi(macro_str.substr(0, macro_str.length() - 1));
}

//! Catches a fatal exception and exits the program
void catch_fatal_exception(exception& e) {
  cout << "Exception: " << e.what() << endl;
  exit(1);
}

//! Checks that the doc has member given by `mem_name`, returns true if member exists
bool check_doc_has_member(const rapidjson::Value& doc, const char mem_name[], string& e_string) {
  bool has_mem = true;
  if (!doc.HasMember(mem_name)) {
    has_mem = false;
    e_string = '"' + (string)mem_name + "\" not specified!";
    throw runtime_error(e_string);
  }
  return has_mem;
}

//! Checks that the index `ind` is a valid index in the given `doc` array indicated by `mem_name`
bool check_doc_valid_array_index(const rapidjson::Value& doc, const char mem_name[], 
                                 rapidjson::SizeType ind, string& e_string) {
  bool is_valid = true;
  if (ind >= doc[mem_name].Size()) {
    is_valid = false;
    e_string = "Access error: array index for \"" + (string)mem_name + "\" is too large.";
    throw runtime_error(e_string);
  }
  return is_valid;
}

//! Checks the given JSON member is an object
void check_doc_member_object(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsObject()) {
      e_string = '"' + (string)mem_name + "\" must be an object!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a number
void check_doc_member_number(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsNumber()) {
      e_string = '"' + (string)mem_name + "\" must be a number!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a number in the `mem_name` array at `ind`
void check_doc_member_number(const rapidjson::Value& doc, const char mem_name[],
                              rapidjson::SizeType ind) {
  string e_string;
  try {
    bool is_valid_index = check_doc_valid_array_index(doc, mem_name, ind, e_string);
    if (is_valid_index && !doc[mem_name][ind].IsNumber()) {
      e_string = "Members of \"" + (string)mem_name + "\" array must be numbers!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is an integer
void check_doc_member_int(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsInt()) {
      e_string = '"' + (string)mem_name + "\" must be a string!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is an array
void check_doc_member_array(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsArray()) {
      e_string = '"' + (string)mem_name + "\" must be an array!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a string
void check_doc_member_string(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsString()) {
      e_string = '"' + (string)mem_name + "\" must be a string!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a string in the `mem_name` array at `ind`
void check_doc_member_string(const rapidjson::Value& doc, const char mem_name[],
                              rapidjson::SizeType ind) {
  string e_string;
  try {
    bool is_valid_index = check_doc_valid_array_index(doc, mem_name, ind, e_string);
    if (is_valid_index && !doc[mem_name][ind].IsString()) {
      e_string = "Members of \"" + (string)mem_name + "\" array must be strings!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}