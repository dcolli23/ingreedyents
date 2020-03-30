#include "JSONFuncs.h"
#include "gtest/gtest.h"

#include "rapidjson/document.h"

#include <string>
#include <iostream>
using namespace std;

const string JSON_EX_FILE_1 = "../tests/data/example_nutrient.json";

class JSONFuncsTest : public testing::Test {
  protected :
    rapidjson::Document* p_doc = new rapidjson::Document();
    string* p_e_string = new string("");

    void SetUp() override {
      JSONFuncs::parse_json(JSON_EX_FILE_1, *p_doc);
    }
};

TEST_F(JSONFuncsTest, CheckHasMemberTrue) {
  bool truth = true;
  bool test = JSONFuncs::check_doc_has_member(*p_doc, "nutrient", *p_e_string);
  EXPECT_EQ(test, truth);
}

TEST_F(JSONFuncsTest, CheckHasMemberFalse) {
  EXPECT_THROW(JSONFuncs::check_doc_has_member(*p_doc, "garbage", *p_e_string), std::runtime_error);
}

// TEST_F(JSONFuncsTest, CheckValidArrayIndexTrue) {

// }

// TEST_F(JSONFuncsTest, CheckValidArrayIndexFalse) {

// }

TEST_F(JSONFuncsTest, CheckMemberObjectTrue) {
  // bool truth = true;
  // bool test = 
  JSONFuncs::check_doc_member_object(*p_doc, "nutrient");
  // EXPECT_EQ(test, truth);
}

// TEST_F(JSONFuncsTest, CheckMemberObjectFalse) {
//   EXPECT_THROW(JSONFuncs::check_doc_member_object(*p_doc, "garbage"), std::runtime_error);
// }

TEST_F(JSONFuncsTest, CheckMemberNumberTrue) {
  // bool truth = true;
  // bool test = 
  JSONFuncs::check_doc_member_number(*p_doc, "id");
  // EXPECT_EQ(test, truth);
}

// TEST_F(JSONFuncsTest, CheckMemberNumberFalse) {

// }

// TEST_F(JSONFuncsTest, CheckMemberNumberArrayTrue) {

// }

// TEST_F(JSONFuncsTest, CheckMemberNumberArrayFalse) {

// }

TEST_F(JSONFuncsTest, CheckMemberIntTrue) {
  JSONFuncs::check_doc_member_int(*p_doc, "id");
}

// TEST_F(JSONFuncsTest, CheckMemberIntFalse) {

// }

// TEST_F(JSONFuncsTest, CheckMemberIntArrayTrue) {

// }

// TEST_F(JSONFuncsTest, CheckMemberIntArrayFalse) {

// }

// TEST_F(JSONFuncsTest, CheckMemberArrayTrue) {

// }

// TEST_F(JSONFuncsTest, CheckMemberArrayFalse) {

// }

TEST_F(JSONFuncsTest, CheckStringMemberTrue) {
//   rapidjson::Document doc;
//   JSONFuncs::parse_json(JSON_EX_FILE_1, doc);

//   // bool truth =
  JSONFuncs::check_doc_member_string(*p_doc, "type");
}

// TEST_F(JSONFuncsTest, CheckMemberStringFalse) {

// }

// TEST_F(JSONFuncsTest, CheckMemberStringArrayTrue) {

// }

// TEST_F(JSONFuncsTest, CheckMemberStringArrayFalse) {

// }