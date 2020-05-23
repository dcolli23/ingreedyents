#pragma once
#include "JSONFuncs.h"
#include "Nutrient.h"
#include "Measurement.h"

#include "rapidjson/document.h"

#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

const int INVALID_INT = -1;
const string INVALID_STRING = "INVALID_STRING";
const double INVALID_DOUBLE = -1.0;

//! Class for parsing the body of the HTTPS GET request
/*!
 * Responsible for parsing the body of the HTTPS GET request (a JSON string) and storing results
 * in this class.
 */
class IngredientResult {
public:
  IngredientResult(string json_result_string);
  IngredientResult(ifstream&);
  ~IngredientResult();

  void set_body(string body);
  
  string get_body();
  int get_ID();
  string get_ingredient_name();
  // double get_calories();
  // int get_carbs();
  // int get_fat();
  // int get_protein();
  Measurement get_serving_size();

  void parse_body();

  map<string, Nutrient*> nutrients;

private:
  string body;

  int get_macro_gram_amount(string macro_str);
  
  // Ingredient information.
  int ID;
  string ingredient_name;
  Measurement serving_size;
};