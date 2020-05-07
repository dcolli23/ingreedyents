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
  URL = BASE_URL;
}

//! Destructor
IngredientRequest::~IngredientRequest() {
  if (result)
    delete result;
  if (getter)
    delete getter;
}

//! Replaces the formatted URL with the UPC and API key supplied
void IngredientRequest::form_URL() {
  int start_idx;
  int substr_len = UPC_FORMATTER.length();

  start_idx = URL.find(UPC_FORMATTER);
  URL.replace(start_idx, substr_len, UPC);

  URL += "apiKey=" + API_key;
}

//! Returns the URL
string IngredientRequest::get_URL() { return URL; }

//! Returns the result of the request made with the formed URL.
//! 
//! Note: `IngredientRequest::form_URL` must be called before this function.
IngredientResult* IngredientRequest::make_request() {
  // Make the request with the HTTPSGETter.
  getter = new HTTPSGETter();
  getter->set_URL(URL);
  getter->make_request();

  // Parse the result with the IngredientResult.
  result = new IngredientResult(getter->get_request_body());

  return result;
}