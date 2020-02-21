#include "example.h"
#include "HTTPRequest.hpp"
#include <iostream>
#include <string>
using namespace std;

int main () {
  example my_example;
  my_example.print_hello();

  // Attempting to make an HTTP request.
  try
  {
    http::Request request("http://postman-echo.com/get?foo1=bar1&foo2=bar2");

    // send a get request.
    const http::Response getResponse = request.send("GET");
    cout << string(getResponse.body.begin(), getResponse.body.end()) << endl;
  }
  catch (const std::exception& e)
  {
    cerr << "Request failed, error: " << e.what() << endl;
  }
  return 0;
}