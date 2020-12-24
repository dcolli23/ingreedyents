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
  uniTypes::RatioBase* get_serving();

  void set_serving(uniTypes::RatioBase*);
  void set_name(string);

private:
  string name;

  // Storing as RatioBase since we're not sure what unit the serving is in.
  uniTypes::RatioBase* serving;
};