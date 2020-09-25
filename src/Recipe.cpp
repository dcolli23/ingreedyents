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
  for (auto & [key, value] : ingredients) {
    delete value;
    value = nullptr;
  }
}

//! Returns the serving size information
uniTypes::Mass Recipe::get_serving() { return serving; }

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
void Recipe::add_ingredient(Ingredient* ing, uniTypes::Mass serv) {
  Nutrient* existing_nut;
  int ingID = ing->get_ID();
  uniTypes::Mass ing_serv_size = ing->get_serving_size();
  double num_servings = serv / ing_serv_size;

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
    uniTypes::Mass nut_serv = nut->get_serving();
    if (nutrition_info.find(nutID) == nutrition_info.end()) {
      // The nutrient is new and we can directly add the nutrient.
      nutrition_info[nutID] = nut;
      nutrient_amounts[nutID] = nut_serv * num_servings;
    }
    else {
      // Otherwise, we have to tally the nutrient amount to our existing amount.
      uniTypes::Mass tot_nut_serv = nut_serv * num_servings;
      nutrient_amounts[nutID] = nutrient_amounts[nutID] + tot_nut_serv;
    }
  }
}

//! Subtract given amount from ingredient with given ID
void Recipe::subtract_ingredient(int ingID, uniTypes::Mass ing_amount_subtracted) {
  double num_servings_removed;
  uniTypes::Mass nutrient_serving_in_ing;

  // Make sure the ingredient exists in our list.
  map<int, Ingredient*>::iterator ingIt = ingredients.find(ingID);
  if (ingIt != ingredients.end()) {
    // It's in our ingredient list.
    map<int, uniTypes::Mass>::iterator ingAmountIt = ingredient_amounts.find(ingID);
    uniTypes::Mass new_amount = ingAmountIt->second - ing_amount_subtracted;
    
    // Remove the ingredient if it is less than or equal to zero.
    if (new_amount.getValue() <= 0.0) {
      remove_ingredient(ingID);
    }
    else {
      // Calculate the number of servings removed for calculating the new amount of nutrients in 
      // recipe.
      uniTypes::Mass ingredient_serving_size = ingredients[ingID]->get_serving_size();
      num_servings_removed = ing_amount_subtracted / ingredient_serving_size;

      // Set the new amount of the ingredient in the recipe.
      ingAmountIt->second = new_amount;

      // Calculate the remaining nutrients in the recipe.
      for (auto const& [nutID, nut] : ingIt->second->nutrients) {
        nutrient_serving_in_ing = ingIt->second->nutrients[nutID]->get_serving();
        uniTypes::Mass tot_nutrient_removed = nutrient_serving_in_ing * num_servings_removed;
        nutrient_amounts[nutID] -= tot_nutrient_removed;
      }
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
  map<int, Ingredient*>::iterator ingIt = ingredients.find(ingID);
  if (ingIt != ingredients.end()) {
    // It's in our ingredient list.
    
    // We have to remove the nutrients coming from this ingredient from our recipe.
    uniTypes::Mass ing_serv_size = ingIt->second->get_serving_size();
    double num_servings_removed = ingredient_amounts[ingID] / ing_serv_size;
    for (auto const& [nutID, nut] : ingIt->second->nutrients) {
      uniTypes::Mass nut_serv = nut->get_serving();
      uniTypes::Mass tot_nut_removed = nut_serv * num_servings_removed;
      nutrient_amounts[nutID] -= tot_nut_removed;
      
      // Remove the nutrient entirely if there's none left.
      if (nutrient_amounts[nutID].getValue() <= 0) {
        nutrient_amounts.erase(nutID);
        nutrition_info.erase(nutID);
      }
    }

    // Erase the ingredient from our recipe.
    ingredients.erase(ingIt);
    ingredient_amounts.erase(ingID);
  }
  else {
    // It's not in our ingredient list.
    cout << "That ingredient is somehow not in your list of ingredients to remove!" << endl;
  }
}