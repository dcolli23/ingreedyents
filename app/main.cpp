#include "UPC_CLI.h"
#include "JSONFuncs.h"
#include "Nutrient.h"

#include "rapidjson/document.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

const string NUTRIENT_FILE = "../tests/data/example_nutrient.json";

int main () {
  // UPC_CLI my_cli = UPC_CLI();
  // my_cli.start_CLI();
  rapidjson::Document doc;
  JSONFuncs::parse_json(NUTRIENT_FILE, doc);
  int my_id = doc["id"].GetInt();
  cout << "Nutrient id: " << my_id << endl;

  // Nutrient my_nutrient(doc);

  // cout << "My nutrient initialized correctly with name: " << my_nutrient.get_name() << endl;

  return 0;
}