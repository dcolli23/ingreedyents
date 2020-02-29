#include <curl/curl.h>

#include <string>
using namespace std; 

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