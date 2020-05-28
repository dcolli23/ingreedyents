#include "Recipe.h"
#include "Measurement.h"
#include "gtest/gtest.h"

#include <string>
using namespace std;

const string MM_ING_FILEPATH = "../tests/data/ingredient_nutrition_get_result.json";
const string MARSH_ING_FILEPATH = "../tests/data/marshmellow_fluff_ingredient.json";

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
    IngredientResult *mmIng, *marshIng;
    Measurement mes1, mes2;

    void SetUp() override {
      my_recipe = new Recipe();

      ifstream mmFin(MM_ING_FILEPATH);
      ifstream marshFin(MARSH_ING_FILEPATH);

      mes1.set_amount(60.0);
      mes1.set_unit("g");
      mes2.set_amount(75.0);
      mes2.set_unit("g");

      if (mmFin.fail() || marshFin.fail()) {
        cout << "File failed to open!" << endl;
      }
      mmIng = new IngredientResult(mmFin);
      marshIng = new IngredientResult(marshFin);
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
  struct Measurement mes_truth = my_recipe->get_serving();
  EXPECT_EQ(mes_truth.get_amount(), 0);
  EXPECT_EQ(mes_truth.get_unit(), "");
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
  double num_mm_servings = mes1 / mmIng->get_serving_size();

  Measurement calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings;

  EXPECT_TRUE(my_recipe->nutrient_amounts["Calcium, Ca"] == calcium_truth);

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
  
  Measurement calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings 
    + marshIng->nutrients["Calcium, Ca"]->get_serving() * num_marsh_servings;
  Measurement energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Energy"]->get_serving() * num_marsh_servings;
  Measurement protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Protein"]->get_serving() * num_marsh_servings;
  Measurement fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Total lipid (fat)"]->get_serving() * num_marsh_servings;  
  Measurement carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_marsh_servings;

  EXPECT_TRUE(my_recipe->nutrient_amounts["Calcium, Ca"] == calcium_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Energy"] == energy_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Protein"] == protein_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Total lipid (fat)"] == fat_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Carbohydrate, by difference"] == carb_truth);

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
  marshIng = nullptr;
}

TEST_F(RecipeWithMultipleIngredients, SubtractIngredientPartialTest) {
  // Add the ingredients.
  my_recipe->add_ingredient(mmIng, mes1);
  my_recipe->add_ingredient(marshIng, mes2);

  Measurement mes_removed = mes2 / 2;

  my_recipe->subtract_ingredient(marshIng->get_ID(), mes_removed);

  // Now check that the nutrients are tallied correctly.
  double num_mm_servings = mes1 / mmIng->get_serving_size();
  double num_marsh_servings = (mes2 - mes_removed) / marshIng->get_serving_size();
  
  Measurement calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings 
    + marshIng->nutrients["Calcium, Ca"]->get_serving() * num_marsh_servings;
  Measurement energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Energy"]->get_serving() * num_marsh_servings;
  Measurement protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Protein"]->get_serving() * num_marsh_servings;
  Measurement fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Total lipid (fat)"]->get_serving() * num_marsh_servings;  
  Measurement carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings
    + marshIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_marsh_servings;

  EXPECT_TRUE(my_recipe->nutrient_amounts["Calcium, Ca"] == calcium_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Energy"] == energy_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Protein"] == protein_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Total lipid (fat)"] == fat_truth);
  EXPECT_TRUE(my_recipe->nutrient_amounts["Carbohydrate, by difference"] == carb_truth);

  // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
  mmIng = nullptr;
  marshIng = nullptr;
}

// TEST_F(RecipeWithMultipleIngredients, RemoveIngredientThroughSubtractionTest) {
//   // Add the ingredients.
//   my_recipe->add_ingredient(mmIng, mes1);
//   my_recipe->add_ingredient(marshIng, mes2);

//   my_recipe->subtract_ingredient(marshIng->get_ID(), mes2);

//   // Now check that the nutrients are tallied correctly.
//   double num_mm_servings = mes1 / mmIng->get_serving_size();  
//   Measurement calcium_truth = mmIng->nutrients["Calcium, Ca"]->get_serving() * num_mm_servings;
//   Measurement energy_truth = mmIng->nutrients["Energy"]->get_serving() * num_mm_servings;
//   Measurement protein_truth = mmIng->nutrients["Protein"]->get_serving() * num_mm_servings;
//   Measurement fat_truth = mmIng->nutrients["Total lipid (fat)"]->get_serving() * num_mm_servings;  
//   Measurement carb_truth = mmIng->nutrients["Carbohydrate, by difference"]->get_serving() * num_mm_servings;

//   EXPECT_TRUE(my_recipe->nutrient_amounts["Calcium, Ca"] == calcium_truth);
//   EXPECT_TRUE(my_recipe->nutrient_amounts["Energy"] == energy_truth);
//   EXPECT_TRUE(my_recipe->nutrient_amounts["Protein"] == protein_truth);
//   EXPECT_TRUE(my_recipe->nutrient_amounts["Total lipid (fat)"] == fat_truth);
//   EXPECT_TRUE(my_recipe->nutrient_amounts["Carbohydrate, by difference"] == carb_truth);

//   // mmIng is deleted with the recipe so set to nullptr here to avoid double free.
//   mmIng = nullptr;
// }

// TEST_F(RecipeWithMultipleIngredients, RemoveIngredientThroughSubtractionTest) {

// }

// TEST_F(RecipeWithMultipleIngredients, RemoveIngredientTest) {

// }