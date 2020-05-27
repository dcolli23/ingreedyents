#include "Measurement.h"

//! Constructor
Measurement::Measurement() {
  amount = 0.0;
  unit = "";
}

//! Constructor
Measurement::Measurement(double amt, string unt) {
  amount = amt;
  unit = unt;
}

//! Returns the amount in the measurement
double Measurement::get_amount() { return amount; }

//! Returns the unit of the measurement
string Measurement::get_unit() { return unit; }

//! Sets the amount of the measurement
void Measurement::set_amount(double amt) { amount = amt; }

//! Sets the unit of the measurement
void Measurement::set_unit(string ut) { unit = ut; }

Measurement Measurement::operator+(Measurement const& mes) {
  Measurement new_mes;
  if (unit == mes.unit) {
    new_mes.unit = unit;
    new_mes.amount = amount + mes.amount;
  }
  else {
    cout << "We don't support unit conversions yet!";
    exit(1);
  }
  return new_mes;
}

Measurement Measurement::operator-(Measurement const& mes) {
  Measurement new_mes;
  if (unit == mes.unit) {
    new_mes.unit = unit;
    new_mes.amount = amount - mes.amount;
  }
  else {
    cout << "We don't support unit conversions yet!";
    exit(1);
  }

  // Check to make sure we don't have negative measurements.
  if (new_mes.amount < 0.0) {
    cout << "Your measurement went below zero!";
    exit(1);
  }
  return new_mes;
}

double Measurement::operator/(Measurement const& mes) {
  double num_servings;
  if (unit == mes.unit) {
    num_servings = amount / mes.amount;
  }
  else {
    cout << "We don't support unit conversions yet!" << endl;
    exit(1);
  }
  return num_servings;
}

Measurement Measurement::operator*(double factor) {
  Measurement new_mes;
  new_mes.amount = amount * factor;
  new_mes.unit = unit;
  return new_mes;
}

Measurement Measurement::operator/(double factor) {
  Measurement new_mes;
  new_mes.amount = amount / factor;
  new_mes.unit = unit;
  return new_mes;
}

Measurement& Measurement::operator+=(Measurement const& mes) {
  if (unit == mes.unit) {
    amount += mes.amount;
  }
  else {
    cout << "We don't support unit conversions yet!";
    exit(1);
  }
  return *this;
}

Measurement& Measurement::operator-=(Measurement const& mes) {
  if (unit == mes.unit) {
    amount -= mes.amount;
  }
  else {
    cout << "We don't support unit conversions yet!";
    exit(1);
  }

  if (amount < 0.0) {
    cout << "You can't have a negative measurement!";
    exit(1);
  }
  return *this;
}

bool Measurement::operator==(Measurement & mes) {
  return amount == mes.amount && unit == mes.unit;
}