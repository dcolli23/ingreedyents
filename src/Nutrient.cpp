#include "Nutrient.h"

//! Constructor
Nutrient::Nutrient(const rapidjson::Value& val) {
  JSONFuncs::check_doc_member_object(val, "nutrient");
  JSONFuncs::check_doc_member_string(val["nutrient"], "name");
  name = val["nutrient"]["name"].GetString();

  JSONFuncs::check_doc_member_number(val, "amount");
  double serving_amount = val["amount"].GetDouble();

  JSONFuncs::check_doc_member_string(val["nutrient"], "unitName");
  string unit_name = val["nutrient"]["unitName"].GetString();
  uniTypes::Mass serving_unit = uniTypes::string_to_mass_unit.at(unit_name);

  uniTypes::Mass serving_size = serving_amount * serving_unit;

  set_serving(serving_size);
}

//! Destructor
Nutrient::~Nutrient() {}

//! Returns the name of the nutrient
string Nutrient::get_name() { return name; }

//! Returns the serving size of this Nutrient
uniTypes::Mass Nutrient::get_serving() { return serving; }

//! Sets the serving for this Nutrient
void Nutrient::set_serving(uniTypes::Mass& mes) { serving = mes; }