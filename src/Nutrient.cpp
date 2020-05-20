#include "Nutrient.h"

//! Constructor
Nutrient::Nutrient(const rapidjson::Value& val) {
  JSONFuncs::check_doc_member_object(val, "nutrient");
  JSONFuncs::check_doc_member_string(val["nutrient"], "name");
  name = val["nutrient"]["name"].GetString();

  JSONFuncs::check_doc_member_number(val, "amount");
  amount = val["amount"].GetDouble();

  JSONFuncs::check_doc_member_string(val["nutrient"], "unitName");
  unit = val["nutrient"]["unitName"].GetString();
}

//! Destructor
Nutrient::~Nutrient() {}

//! Returns the name of the nutrient
string Nutrient::get_name() { return name; }

//! Returns the amount of the nutrient per serving
double Nutrient::get_amount() { return amount; }

//! Returns the unit of the nutrient amount per serving
string Nutrient::get_unit() { return unit; }