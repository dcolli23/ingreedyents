#pragma once
#include "JSONFuncs.h"
#include "Measurement.h"

#include <rapidjson/document.h>

#include <string>
using namespace std;

class Nutrient {
public:
  Nutrient(const rapidjson::Value& val);
  ~Nutrient();

  string get_name();
  Measurement get_serving();

private:
  string name;
  Measurement serving;
};