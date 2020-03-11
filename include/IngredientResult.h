#include "JSONErr.h"

#include "rapidjson/document.h"

#include <string>
#include <iostream>
using namespace std;

//! Class for parsing the body of the HTTPS GET request
/*!
 * Responsible for parsing the body of the HTTPS GET request (a JSON string) and storing results
 * in this class.
 */
class IngredientResult {
public:
  IngredientResult(string json_result_string);
  ~IngredientResult();

  void set_body(string body);
  string get_body();
  double get_calories();
  int get_carbs();
  int get_fat();
  int get_protein();

  void parse_body();

private:
  string body;

  int get_macro_gram_amount(string macro_str);
  
  // Ingredient information.
  int ID;
  string ingredient_name;
  double calories;
  int carbs_grams;
  int fat_grams;
  int protein_grams;

};