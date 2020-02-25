#include "example.h"
// #include "HTTPRequest.hpp"
#include "httplib.h"
#include <iostream>
#include <string>
using namespace std;

const int HTTPS_PORT = 443;

int main () {
  example my_example;
  my_example.print_hello();

  string protocol = "https://";
  string base_url = "api.spoonacular.com";
  string base_local = "/recipes/bagel/information?apiKey=";
  string api_key = "0bd3f2b62e014ddc80ec18210705d8e8";
  // Attempting to make an HTTP request.
  // try
  // {
  //   http::Request request(base_str+api_key);

  //   // send a get request.
  //   const http::Response getResponse = request.send("GET");
  //   cout << string(getResponse.body.begin(), getResponse.body.end()) << endl;
  // }
  // catch (const std::exception& e)
  // {
  //   cerr << "Request failed, error: " << e.what() << endl;
  // }

  // Actually need a library with HTTPS support. Trying out httplib.h now.
  httplib::Client my_cli(base_url, HTTPS_PORT);
  auto res = my_cli.Get((base_local+api_key).c_str());
  cout << res->body << endl;

  // httplib::Client test_cli("httpbin.org");

  // auto res = test_cli.Get("/range/32", {
  //   httplib::make_range_header({{1, 10}})
  // });
  // cout << "res->status: " << res->status << endl;
  // cout << "res->body: " << res->body << endl;
  return 0;
}