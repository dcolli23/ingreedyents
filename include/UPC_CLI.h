#pragma once
#include <iostream>
#include <string>

using namespace std;

class UPC_CLI {
public:
  UPC_CLI();
  ~UPC_CLI();

  void start_CLI();
private:
  string API_key;
};