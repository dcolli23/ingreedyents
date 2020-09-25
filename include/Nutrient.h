#pragma once
#include "JSONFuncs.h"

#include "uniTypes/uniTypes.h"
#include "rapidjson/document.h"

#include <string>
using namespace std;

class Nutrient {
public:
  Nutrient(const rapidjson::Value& val);
  ~Nutrient();

  string get_name();
  uniTypes::Mass get_serving();

  void set_serving(uniTypes::Mass&);
  void set_name(string);

private:
  string name;
  uniTypes::Mass serving;
};