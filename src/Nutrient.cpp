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

  uniTypes::RatioBase* new_serving;
  
  // Get the unit that we're going to work with.
  if (unit_name.compare("IU") == 0) { // This is a dimensionless unit.
    new_serving = new uniTypes::UOBA(serving_amount * uniTypes::IU);
  }
  else { // We're working with mass units
    uniTypes::Mass serving_unit = uniTypes::string_to_mass_unit.at(unit_name);
    new_serving = new uniTypes::Mass(serving_amount * serving_unit);
  }

  set_serving(new_serving);
}

//! Destructor
Nutrient::~Nutrient() {
  delete serving;
}

//! Returns the name of the nutrient
string Nutrient::get_name() { return name; }

//! Returns the serving size of this Nutrient
uniTypes::RatioBase* Nutrient::get_serving() { return serving; }

//! Sets the serving for this Nutrient
void Nutrient::set_serving(uniTypes::RatioBase* mes) { serving = mes; }