#include "Recipe.h"

//! Constructor
Recipe::Recipe() {
  calories_per_serving = 0.0;
  net_carbs_g_per_serving = 0.0;
  protein_g_per_serving = 0.0;
  fat_g_per_serving = 0.0;
  date_of_creation = time(0);
  rating = -1;
  instructions = "";
}

//! Destructor
Recipe::~Recipe() {
  for (auto const& [key, value] : ingredients) {
    delete value;
  }
}

//! Returns the serving size information
Measurement Recipe::get_serving() { return serving; }

//! Returns the calories per serving in kcals
double Recipe::get_calories_per_serving() { return calories_per_serving; }

//! Returns the net carbs per serving in grams
//!
//! Net carbs are calculated as total carbs minus the fiber content.
double Recipe::get_net_carbs_g_per_serving() { return net_carbs_g_per_serving; }

//! Return the protein per serving in grams
double Recipe::get_protein_g_per_serving(){ return protein_g_per_serving; }

//! Return the fat per serving in grams
double Recipe::get_fat_g_per_serving() { return fat_g_per_serving; }

//! Return the date the recipe was created
time_t Recipe::get_date_of_creation() { return date_of_creation; }

//! Return the rating of the recipe
int Recipe::get_rating() { return rating; }

//! Return the instructions for making the recipe
string Recipe::get_instructions() { return instructions; }

//! Add an ingredient to the recipe
void Recipe::add_ingredient(IngredientResult* ing, Measurement serv) {
  Nutrient* existing_nut;
  int ingID = ing->get_ID();

  // Tally the ingredient and the amount into our ingredients list.
  if (ingredients.find(ingID) == ingredients.end()) {
    // The ingredient is new and we'll add to our map.
    ingredients[ingID] = ing;
    ingredient_amounts[ingID] = serv;
  }
  else {
    // The ingredient already exists and we just need to tally up the extra amount.
    // Measurement& existing_serv = ingredient_amounts[ingID];
    // if (existing_serv.unit == serv.unit)
    //   existing_serv.amount += serv.amount;
    // else {
      cout << "We don't support unit conversions yet!";
      exit(1);
    // }
  }

  // Tally the nutrition information for this ingredient.
  // for (auto const& [nutID, nut] : ing->nutrients) {
  //   if (nutrition_info.find(nutID) == nutrition_info.end()) {
  //     // The nutrient is new and we can directly add the nutrient.
  //     nutrition_info[nutID] = nut;
  //   }
  //   else {
  //     // Otherwise, we have to tally the nutrient amount to our existing amount.
  //     nutrition_info[nutID]->add_measurement_to_serving(serv);
  //   }
  // }
}

//! Remove an ingredient from the recipe