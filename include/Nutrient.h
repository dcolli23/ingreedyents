#pragma once
#include "JSONFuncs.h"

#include <rapidjson/document.h>

#include <string>
using namespace std;

class Nutrient {
public:
  Nutrient(rapidjson::Value& val);
  ~Nutrient();

  string get_name();
  double get_amount();
  string get_unit();

private:
  string name;
  double amount;
  string unit;
};