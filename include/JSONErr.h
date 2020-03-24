#pragma once
#include <rapidjson/document.h>

#include <iostream>
#include <string>
using namespace std;

namespace JSONErr {
  void catch_fatal_exception(exception& e);
  bool check_doc_has_member(const rapidjson::Value& doc, const char mem_name[], string& e_string);
  bool check_doc_valid_array_index(const rapidjson::Value& doc, const char mem_name[], 
                                  rapidjson::SizeType ind, string& e_string);
  void check_doc_member_object(const rapidjson::Value& doc, const char mem_name[]);
  void check_doc_member_number(const rapidjson::Value& doc, const char mem_name[]);
  void check_doc_member_number(const rapidjson::Value& doc, const char mem_name[],
                                rapidjson::SizeType ind);
  void check_doc_member_int(const rapidjson::Value& doc, const char mem_name[]);
  void check_doc_member_array(const rapidjson::Value& doc, const char mem_name[]);
  void check_doc_member_string(const rapidjson::Value& doc, const char mem_name[]);
  void check_doc_member_string(const rapidjson::Value& doc, const char mem_name[],
                                rapidjson::SizeType ind);
}