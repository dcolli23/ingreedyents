#include "JSONErr.h"

//! Catches a fatal exception and exits the program
void JSONErr::catch_fatal_exception(exception& e) {
  cout << "Exception: " << e.what() << endl;
  exit(1);
}

//! Checks that the doc has member given by `mem_name`, returns true if member exists
bool JSONErr::check_doc_has_member(const rapidjson::Value& doc, const char mem_name[], 
                                   string& e_string) {
  bool has_mem = true;
  if (!doc.HasMember(mem_name)) {
    has_mem = false;
    e_string = '"' + (string)mem_name + "\" not specified!";
    throw runtime_error(e_string);
  }
  return has_mem;
}

//! Checks that the index `ind` is a valid index in the given `doc` array indicated by `mem_name`
bool JSONErr::check_doc_valid_array_index(const rapidjson::Value& doc, const char mem_name[], 
                                          rapidjson::SizeType ind, string& e_string) {
  bool is_valid = true;
  if (ind >= doc[mem_name].Size()) {
    is_valid = false;
    e_string = "Access error: array index for \"" + (string)mem_name + "\" is too large.";
    throw runtime_error(e_string);
  }
  return is_valid;
}

//! Checks the given JSON member is an object
void JSONErr::check_doc_member_object(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsObject()) {
      e_string = '"' + (string)mem_name + "\" must be an object!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a number
void JSONErr::check_doc_member_number(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsNumber()) {
      e_string = '"' + (string)mem_name + "\" must be a number!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a number in the `mem_name` array at `ind`
void JSONErr::check_doc_member_number(const rapidjson::Value& doc, const char mem_name[],
                                      rapidjson::SizeType ind) {
  string e_string;
  try {
    bool is_valid_index = check_doc_valid_array_index(doc, mem_name, ind, e_string);
    if (is_valid_index && !doc[mem_name][ind].IsNumber()) {
      e_string = "Members of \"" + (string)mem_name + "\" array must be numbers!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is an integer
void JSONErr::check_doc_member_int(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsInt()) {
      e_string = '"' + (string)mem_name + "\" must be a string!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is an array
void JSONErr::check_doc_member_array(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsArray()) {
      e_string = '"' + (string)mem_name + "\" must be an array!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a string
void JSONErr::check_doc_member_string(const rapidjson::Value& doc, const char mem_name[]) {
  string e_string;
  try {
    bool has_member = check_doc_has_member(doc, mem_name, e_string);
    if (has_member && !doc[mem_name].IsString()) {
      e_string = '"' + (string)mem_name + "\" must be a string!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}

//! Checks the given JSON member is a string in the `mem_name` array at `ind`
void JSONErr::check_doc_member_string(const rapidjson::Value& doc, const char mem_name[],
                                      rapidjson::SizeType ind) {
  string e_string;
  try {
    bool is_valid_index = check_doc_valid_array_index(doc, mem_name, ind, e_string);
    if (is_valid_index && !doc[mem_name][ind].IsString()) {
      e_string = "Members of \"" + (string)mem_name + "\" array must be strings!";
      throw runtime_error(e_string);
    }
  }
  catch (exception& e) {
    catch_fatal_exception(e);
  }
}