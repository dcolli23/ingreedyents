#include "Recipe.h"
#include "Measurement.h"
#include "gtest/gtest.h"

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

TEST_F(RecipeTest, InitializationTest) {
  EXPECT_TRUE(my_recipe->ingredients.empty());
  EXPECT_TRUE(my_recipe->ingredient_amounts.empty());
  struct Measurement mes_truth = my_recipe->get_serving();
  EXPECT_EQ(mes_truth.amount, 0);
  EXPECT_EQ(mes_truth.unit, "");
  EXPECT_EQ(my_recipe->get_calories_per_serving(), 0);
  EXPECT_EQ(my_recipe->get_net_carbs_g_per_serving(), 0);
  EXPECT_EQ(my_recipe->get_protein_g_per_serving(), 0);
  EXPECT_EQ(my_recipe->get_fat_g_per_serving(), 0);
  EXPECT_LE(my_recipe->get_date_of_creation(), time(0));
  EXPECT_EQ(my_recipe->get_rating(), -1);
  EXPECT_EQ(my_recipe->get_instructions(), "");
}