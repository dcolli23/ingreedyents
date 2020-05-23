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
    ingredient_amounts[ingID] += serv;
  }

  // Tally the nutrition information for this ingredient.
  for (auto const& [nutID, nut] : ing->nutrients) {
    if (nutrition_info.find(nutID) == nutrition_info.end()) {
      // The nutrient is new and we can directly add the nutrient.
      nutrition_info[nutID] = nut;
    }
    else {
      // Otherwise, we have to tally the nutrient amount to our existing amount.
      // nutrition_info[nutID]->set_serving(nutrition_info[nutID]->get_serving() + serv * nut->get_serving());
      cout << "Nutrition tallying isn't implemented yet!";
    }
  }
}

//! Subtract given amount from ingredient with given ID
void Recipe::subtract_ingredient(int ingID, Measurement serv) {
  // Make sure the ingredient exists in our list.
  map<int, IngredientResult*>::iterator ingIt = ingredients.find(ingID);
  if (ingIt != ingredients.end()) {
    // It's in our ingredient list.
    map<int, Measurement>::iterator ingAmountIt = ingredient_amounts.find(ingID);
    double new_amount = ingAmountIt->second.get_amount() - serv.get_amount();
    
    // Remove the ingredient if it is less than or equal to zero.
    if (new_amount <= 0.0) {
      remove_ingredient(ingID);
    }
    else {
      ingAmountIt->second.set_amount(new_amount);
    }
  }
  else {
    // It's not in our list.
    cout << "That ingredient is somehow not in your list of ingredients for this recipe!" << endl;
  }
}

//! Remove an ingredient from the recipe
void Recipe::remove_ingredient(int ingID) {
  // Make sure the ingredient exists in our list.
  map<int, IngredientResult*>::iterator ingIt = ingredients.find(ingID);
  if (ingIt != ingredients.end()) {
    // It's in our ingredient list.
    ingredients.erase(ingIt);
    ingredient_amounts.erase(ingID);
  }
  else {
    // It's not in our ingredient list.
    cout << "That ingredient is somehow not in your list of ingredients to remove!" << endl;
  }
}