#include "IngredientRequest.h"


//! Returns an instance of the IngredientRequest class
//!
//! This class is meant to handle the retrieval and parsing of an ingredient when supplied the
//! UPC via an HID (human interface device).
IngredientRequest::IngredientRequest(string UPC, string API_key) {
  this->API_key = API_key;
  this->UPC = UPC;
  result = nullptr;
  getter = nullptr;
  FDC_ID_URL = FDC_ID_BASE_URL;
  detailed_nutrition_URL = DETAILED_NUTRITION_BASE_URL;
}

//! Destructor
IngredientRequest::~IngredientRequest() {
  if (result)
    delete result;
  if (getter)
    delete getter;
}

//! Replaces the formatted FDC ID URL with the UPC and API key supplied
void IngredientRequest::form_FDC_ID_URL() {
  int start_idx;
  int substr_len = UPC_FORMATTER.length();

  start_idx = FDC_ID_URL.find(UPC_FORMATTER);
  FDC_ID_URL.replace(start_idx, substr_len, UPC);

  FDC_ID_URL += "&apiKey=" + API_key;
}

//! Forms the URL for GETting the detailed nutrition information given the FDC ID
void IngredientRequest::form_detailed_nutrition_URL() {
  detailed_nutrition_URL += FDC_ID + "?apiKey=" + API_key;
}

//! Returns the URL for making the initial request for finding the FDC ID
string IngredientRequest::get_FDC_ID_URL() { return FDC_ID_URL; }

//! Returns the URL for making the second request for the detailed nutrition information
string IngredientRequest::get_detailed_nutrition_URL() { return detailed_nutrition_URL; }

//! Returns the result of the request made with the formed URL.
//! 
//! Note: `IngredientRequest::form_URL` must be called before this function.
IngredientResult* IngredientRequest::make_request() {
  rapidjson::Document doc;

  // Make the initial request with the HTTPSGETter to get the FDC ID.
  getter = new HTTPSGETter();
  getter->set_URL(FDC_ID_URL);
  getter->make_request();

  // Parse the first result and grab the FDC ID.
  rapidjson::ParseResult parse_ok = doc.Parse(getter->get_request_body().c_str());

  // Ensure that we only got one search result for this UPC lookup and grab that result.
  JSONFuncs::check_doc_member_int(doc, "totalHits");
  if (doc["totalHits"].GetInt() != 1) {
    cout << "More than one search result for your UPC!!" << endl;
    exit(1);
  }
  JSONFuncs::check_doc_member_array(doc, "foods");
  const rapidjson::Value& foodObj = doc["foods"].GetArray()[0];
  FDC_ID = to_string(foodObj["fdcId"].GetInt());
  form_detailed_nutrition_URL();

  // Make the second request to get the detailed nutrition information.
  delete getter;
  getter = new HTTPSGETter();
  getter->set_URL(detailed_nutrition_URL);
  getter->make_request();

  // Parse the result with the IngredientResult.
  result = new IngredientResult(getter->get_request_body());

  return result;
}