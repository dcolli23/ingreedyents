#pragma once
#include "gtest/gtest.h"
#include "IngredientResult.h"
#include <string>
#include <fstream>
#include <iostream>

const std::string JSON_RESULT_LOCATION = "../tests/data/ingredient_get_result.json";

// class JSONResult : public ::testing::Test {
//   protected:
//     JSONResult() {
//       std::ifstream fin(JSON_RESULT_LOCATION);
//       if (fin.fail()) {
//         std::cout << "File failed to load";
//         exit(1);
//       }
//       body = fin.read();
//     }
//   private:
//     std::string body;
// }
// JSON_RESULT_STRING = 

TEST(IngredientResultTest, TestCarbParse) {
  std::string test_body = "{\"a\": 5}";
  IngredientResult ir(test_body);

  ASSERT_EQ(ir.get_body(), test_body);
}