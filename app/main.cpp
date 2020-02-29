#include "example.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

const int HTTPS_PORT = 443;

int main () {
  example my_example;
  my_example.print_hello();

  // string protocol = "https://";
  // string base_url = "api.spoonacular.com";
  // string base_local = "/recipes/bagel/information?apiKey=";
  // string api_key = "0bd3f2b62e014ddc80ec18210705d8e8";

  string protocol = "https://";
  string base_url = "postman-echo.com";
  string base_local = "/get?foo1=bar1&foo2=bar2";

  CURL* curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, (protocol+base_url+base_local).c_str());
    // curl_easy_setopt(curl, CURLOPT_URL, "https://curl.haxx.se/mail/lib-2019-10/0090.html");
    // curl_easy_setopt(curl, CURLOPT_URL, "https://postman-echo.com/get?foo1=bar1&foo2=bar2");

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif 
    // Perform the request. res gets the return code.
    res = curl_easy_perform(curl);

    // Check for errors.
    if (res != CURLE_OK)
      cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

    // Always cleanup
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  
  return 0;
}