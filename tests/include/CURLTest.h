#include <curl/curl.h>
#include "gtest/gtest.h"
#include <string>

TEST(CURLTest, InitCURL) {
  CURL* curl;
  curl = curl_easy_init();
  // EXPECT_EQ(curl, true);
  curl_global_cleanup();
}

TEST(CURLTest, KnownGETRequest) {
  string test_url = "https://postman-echo.com/get?foo1=bar1&foo2=bar2";
  CURL* curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, test_url.c_str());
    res = curl_easy_perform(curl);

    // Check for errors in the result.
    EXPECT_EQ(res, CURLE_OK) << "curl_easy_perform() failed: " << curl_easy_strerror(res);

    // Always cleanup
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

}