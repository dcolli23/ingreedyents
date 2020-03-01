#include <string>
using namespace std;

class IngredientResult {
public:
  IngredientResult(string json_result_string);
  ~IngredientResult();

  string get_body();

private:
  string body;
  
  // Ingredient information.
  string ingredient_name;
  int carbs_grams;
  int fat_grams;
  int protein_grams;

};