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

    void SetUp() override {
      my_recipe = new Recipe();

      ifstream mmFin(MM_ING_FILEPATH);
      ifstream marshFin(MARSH_ING_FILEPATH);

      if (mmFin.fail() || marshFin.fail()) {
        cout << "File failed to open!" << endl;
      }
      mmIng = new IngredientResult(mmFin);
      marshIng = new IngredientResult(marshFin);
    }

    void TearDown() override {
      delete my_recipe;
      delete mmIng;
      delete marshIng;
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
  
}

// TEST_F(RecipeTest, AddMultipleIngredientTest) {

// }

// TEST_F(RecipeTest, SubtractIngredientTest) {

// }

// TEST_F(RecipeTest, RemoveIngredientThroughSubtractionTest) {

// }

// TEST_F(RecipeTest, RemoveIngredientTest) {

// }