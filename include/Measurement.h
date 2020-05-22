#pragma once

#include <string>
#include <iostream>
using namespace std;

class Measurement {
public:
  Measurement();

  // Gets

  double get_amount();
  string get_unit();

  // Sets

  void set_amount(double);
  void set_unit(string);

  Measurement operator+(Measurement const& mes);

private:
  double amount;
  string unit;
};