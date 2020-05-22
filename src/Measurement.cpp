#include "Measurement.h"

//! Constructor
Measurement::Measurement() {
  amount = 0.0;
  unit = "";
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
  if (unit == mes.unit)
    new_mes.amount = amount + mes.amount;
  else {
    cout << "We don't support unit conversions yet!";
    exit(1);
  }
}

