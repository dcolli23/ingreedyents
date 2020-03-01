#include <curl/curl.h>

#include <string>
using namespace std; 

//! Class for making HTTPS GET requests given a UPC
/*!
 * Class for making custom HTTPS GET requests. To make a proper request you must:
 *   + Initialize an instance of the class by supplying the URL.
 *   + Make the request by calling `make_request()`.
 *   + Get the request body as a string by calling `get_request_body()`. 
 */
class HTTPSGETter {
public:
  HTTPSGETter();

  void set_URL(string URL);
  void make_request();
  string get_request_body();

private:
  string URL;
  string request_body;
  static size_t cURL_stdstring_callback_writer(void* contents, size_t size, size_t nmemb, 
    string* s);
};