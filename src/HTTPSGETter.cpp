#include "HTTPSGETter.h"
 
HTTPSGETter::HTTPSGETter() {
  URL = "";
  request_body = "";
}

//! Sets the URL to make the GET request from
void HTTPSGETter::set_URL(string new_URL) { URL = new_URL; }

//! Makes the HTTPS GET request and writes result to `request_body`
void HTTPSGETter::make_request() {
  CURL* curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    // Set the URL.
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

    // Set callback to append results to our request_body string.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cURL_stdstring_callback_writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &request_body);

    // Make the request.
    res = curl_easy_perform(curl);
  }
}

//! Callback function supplied to cURL for writing request result to `request_body`
size_t HTTPSGETter::cURL_stdstring_callback_writer(void* contents, size_t size, size_t nmemb, 
    string* s) {
  size_t new_length = size * nmemb;
  try {
    s->append((char*)contents, new_length);
  }
  catch (bad_alloc &e) {
    // Handle memory problem.
    return 0;
  }
  return new_length;
}

//! Returns `request_body`
string HTTPSGETter::get_request_body() { return request_body; }