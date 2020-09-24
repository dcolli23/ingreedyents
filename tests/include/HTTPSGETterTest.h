#pragma once
#include "HTTPSGETter.h"

#include "gtest/gtest.h"

#include <string>
using namespace std;

TEST(HTTPSGETterTest, InitializationTest) {
  HTTPSGETter my_getter;
}

TEST(HTTPSGETterTest, VerifyGETAgainstKnownSource) {
  HTTPSGETter my_getter;
  string test_URL = "https://postman-echo.com/get?foo1=bar1&foo2=bar2";
  my_getter.set_URL(test_URL);
  my_getter.make_request();
  string request_body = my_getter.get_request_body();

  EXPECT_EQ(request_body.substr(0, 9), "{\"args\":{");
}