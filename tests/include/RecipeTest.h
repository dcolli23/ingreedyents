#pragma once
#include "Recipe.h"
#include "Measurement.h"
#include "gtest/gtest.h"

#include <string>
using namespace std;
using namespace uniTypes::string_literals;

const string MM_ING_FILEPATH = "../tests/data/ingredient_nutrition_get_result.json";
const string MARSH_ING_FILEPATH = "../tests/data/marshmellow_fluff_ingredient.json";
const double ERROR_TOL = 1e-5;

class RecipeTest : public testing::Test {
  protected:
    Recipe* my_recipe;

    void SetUp() override {
      my_recipe = new Recipe();
    }

    void TearDown() override {
      delete my_recipe;
    }
};

class RecipeWithMultipleIngredients : public testing::Test {
  protected:
    Recipe* my_recipe;
    Ingredient *mmIng, *marshIng;
    uniTypes::Mass mes1, mes2;

    void SetUp() override {
      my_recipe = new Recipe();

      ifstream mmFin(MM_ING_FILEPATH);
      ifstream marshFin(MARSH_ING_FILEPATH);

      mes1 = 60.0_g;
      mes2 = 75.0_g;

      if (mmFin.fail() || marshFin.fail()) {
        cout << "File failed to open!" << endl;
      }
      mmIng = new Ingredient(mmFin);
      marshIng = new Ingredient(marshFin);
    }

    void TearDown() override {
      delete my_recipe;
      my_recipe = nullptr;
      if (mmIng) delete mmIng;
      if (marshIng) delete marshIng;
    }
};

TEST_F(RecipeTest, InitializationTest) {
  EXPECT_TRUE(my_recipe->ingredients.empty());
  EXPECT_TRUE(my_recipe->ingredient_amounts.empty());
  uniTypes::Mass mes_truth = my_recipe->get_serving();
  EXPECT_EQ(mes_truth.convertTo(uniTypes::gram), 0);
  // EXPECT_EQ(mes_truth.get_unit(), "");
  EXPECT_EQ(my_recipe->get_calories_per_serving(), 0);
  EXPECT_EQ(my_recipe->get_net_carbs_g_per_serving(), 0);
  EXPECT_EQ(my_recipe->get_protein_g_per_serving(), 0);
  EXPECT_EQ(my_recipe->get_fat_g_per_serving(), 0);
  EXPECT_LE(my_recipe->get_date_of_creation(), time(0));
  EXPECT_EQ(my_recipe->get_rating(), -1);
  EXPECT_EQ(my_recipe->get_instructions(), "");
}

TEST_F(RecipeWithMultipleIngredients, AddIngredientTest) {
  my_recipe->add_ingredient(mmIng, mes1);
  int ID_truth = mmIng->get_ID();
  int ID_test = my_recipe->ingredients[ID_truth]->get_ID();
  EXPECT_EQ(ID_test, ID_truth);

  // Now check that the nutrients are tallied correctly.
  uniTypes::Mass mmIng_serving_size = mmIng->get_serving_size();
  double num_mm_servings = mes1 / mmIng_serving_size;

  uniTypes::Mass calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings;

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].convertTo(uniTypes::gram),
    calcium_truth.convertTo(uniTypes::gram));

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
}

TEST_F(RecipeWithMultipleIngredients, AddMultipleIngredientTest) {
  my_recipe->add_ingredient(mmIng, mes1);
  my_recipe->add_ingredient(marshIng, mes2);

  int ID_truth_1 = mmIng->get_ID();
  int ID_truth_2 = marshIng->get_ID();
  int ID_test_1 = my_recipe->ingredients[ID_truth_1]->get_ID();
  int ID_test_2 = my_recipe->ingredients[ID_truth_2]->get_ID();

  EXPECT_EQ(ID_test_1, ID_truth_1);
  EXPECT_EQ(ID_test_2, ID_truth_2);

  // Now check that the nutrients are tallied correctly.
  double num_mm_servings = mes1 / mmIng->get_serving_size();
  double num_marsh_servings = mes2 / marshIng->get_serving_size();
  
  uniTypes::Mass calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings 
    + marshIng->nutrients["Calcium, Ca"]->get_serving() * num_marsh_servings;
  uniTypes::Mass energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Energy"]->get_serving() * num_marsh_servings;
  uniTypes::Mass protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Protein"]->get_serving() * num_marsh_servings;
  uniTypes::Mass fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Total lipid (fat)"]->get_serving() * num_marsh_servings;  
  uniTypes::Mass carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_marsh_servings;

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].convertTo(uniTypes::gram),
    calcium_truth.convertTo(uniTypes::gram));
  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Energy"].convertTo(uniTypes::gram),
    energy_truth.convertTo(uniTypes::gram));
  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Protein"].convertTo(uniTypes::gram), 
    protein_truth.convertTo(uniTypes::gram));
  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].convertTo(uniTypes::gram),
    fat_truth.convertTo(uniTypes::gram));
  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].convertTo(uniTypes::gram),
    carb_truth.convertTo(uniTypes::gram));

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
  marshIng = nullptr;
}

TEST_F(RecipeWithMultipleIngredients, SubtractIngredientPartialTest) {
  // Add the ingredients.
  my_recipe->add_ingredient(mmIng, mes1);
  my_recipe->add_ingredient(marshIng, mes2);

  uniTypes::Mass mes_removed = mes2 / 2;

  my_recipe->subtract_ingredient(marshIng->get_ID(), mes_removed);

  // Now check that the nutrients are tallied correctly.
  double num_mm_servings = mes1 / mmIng->get_serving_size();
  double num_marsh_servings = (mes2 - mes_removed) / marshIng->get_serving_size();
  
  uniTypes::Mass calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings 
    + marshIng->nutrients["Calcium, Ca"]->get_serving() * num_marsh_servings;
  uniTypes::Mass energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Energy"]->get_serving() * num_marsh_servings;
  uniTypes::Mass protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Protein"]->get_serving() * num_marsh_servings;
  uniTypes::Mass fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Total lipid (fat)"]->get_serving() * num_marsh_servings;  
  uniTypes::Mass carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_marsh_servings;

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].get_amount(), calcium_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].get_unit(), calcium_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Energy"].get_amount(), energy_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Energy"].get_unit(), energy_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Protein"].get_amount(), protein_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Protein"].get_unit(), protein_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].get_amount(), fat_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].get_unit(), fat_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].get_amount(), carb_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].get_unit(), carb_truth.get_unit());

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
  marshIng = nullptr;
}

TEST_F(RecipeWithMultipleIngredients, RemoveIngredientThroughSubtractionTest) {
  // Add the ingredients.
  my_recipe->add_ingredient(mmIng, mes1);
  my_recipe->add_ingredient(marshIng, mes2);

  my_recipe->subtract_ingredient(marshIng->get_ID(), mes2);

  // Now check that the nutrients are tallied correctly.
  double num_mm_servings = mes1 / mmIng->get_serving_size();  
  uniTypes::Mass calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings;
  uniTypes::Mass energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings;
  uniTypes::Mass protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings;
  uniTypes::Mass fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings;  
  uniTypes::Mass carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings;

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].get_amount(), calcium_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].get_unit(), calcium_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Energy"].get_amount(), energy_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Energy"].get_unit(), energy_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Protein"].get_amount(), protein_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Protein"].get_unit(), protein_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].get_amount(), fat_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].get_unit(), fat_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].get_amount(), carb_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].get_unit(), carb_truth.get_unit());

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
}

TEST_F(RecipeWithMultipleIngredients, RemoveIngredientTest) {
  // Add the ingredients.
  my_recipe->add_ingredient(mmIng, mes1);
  my_recipe->add_ingredient(marshIng, mes2);

  my_recipe->subtract_ingredient(marshIng->get_ID(), mes2);

  // Now check that the nutrients are tallied correctly.
  double num_mm_servings = mes1 / mmIng->get_serving_size();  
  uniTypes::Mass calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings;
  uniTypes::Mass energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings;
  uniTypes::Mass protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings;
  uniTypes::Mass fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings;  
  uniTypes::Mass carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings;

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].get_amount(), calcium_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Calcium, Ca"].get_unit(), calcium_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Energy"].get_amount(), energy_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Energy"].get_unit(), energy_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Protein"].get_amount(), protein_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Protein"].get_unit(), protein_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].get_amount(), fat_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Total lipid (fat)"].get_unit(), fat_truth.get_unit());

  EXPECT_FLOAT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].get_amount(), carb_truth.get_amount());
  EXPECT_EQ(my_recipe->nutrient_amounts["Carbohydrate, by difference"].get_unit(), carb_truth.get_unit());

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
}