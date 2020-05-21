#include "Nutrient.h"

//! Constructor
Nutrient::Nutrient(const rapidjson::Value& val) {
  JSONFuncs::check_doc_member_object(val, "nutrient");
  JSONFuncs::check_doc_member_string(val["nutrient"], "name");
  name = val["nutrient"]["name"].GetString();

  JSONFuncs::check_doc_member_number(val, "amount");
  serving.amount = val["amount"].GetDouble();

  JSONFuncs::check_doc_member_string(val["nutrient"], "unitName");
  serving.unit = val["nutrient"]["unitName"].GetString();
}

//! Destructor
Nutrient::~Nutrient() {}

//! Returns the name of the nutrient
string Nutrient::get_name() { return name; }

//! Returns the serving size of this Nutrient
Measurement Nutrient::get_serving() { return serving; }