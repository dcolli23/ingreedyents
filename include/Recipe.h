#pragma once

#include "IngredientResult.h"
#include "Measurement.h"
#include "Nutrient.h"

#include <iostream>
#include <map>
#include <string>
using namespace std;

class Recipe {
public:
  Recipe();
  ~Recipe();

  // Gets

  Measurement get_serving();
  double get_calories_per_serving();
  double get_net_carbs_g_per_serving();
  double get_protein_g_per_serving();
  double get_fat_g_per_serving();
  time_t get_date_of_creation();
  int get_rating();
  string get_instructions();

  void add_ingredient(IngredientResult*, Measurement);
  void subtract_ingredient(int, Measurement);
  void remove_ingredient(int);

  map<int, IngredientResult*> ingredients;
  map<int, Measurement> ingredient_amounts;
  map<string, Nutrient*> nutrition_info;
  map<string, Measurement> nutrient_amounts;

private:
  struct Measurement serving;
  double calories_per_serving;
  double net_carbs_g_per_serving;
  double protein_g_per_serving;
  double fat_g_per_serving;
  time_t date_of_creation;
  int rating;
  string instructions;
};