#include "UPC_CLI.h"
#include "IngredientRequest.h"
#include "IngredientResult.h"

//! Constructor
UPC_CLI::UPC_CLI() {
  cout << "UPC_CLI constructor called" << endl;
}

//! Desctructor
UPC_CLI::~UPC_CLI() {
  cout << "UPC_CLI destructor called" << endl;
}

//! Starts the command line interface for UPC entry
void UPC_CLI::start_CLI() {
  string user_response;
  IngredientRequest* user_request;
  IngredientResult* ing_result;

  // Ask for the API key.
  // cout << "Please enter your unique spoonacular API key: ";
  // cin >> API_key;
  API_key = "0bd3f2b62e014ddc80ec18210705d8e8";

  // Ask for user input of UPC codes and make requests for them.
  while (1) {
    cout << "Please enter the UPC of the product you would like to look up: ";
    cin >> user_response;

    cout << "\tYou entered: " << user_response << endl;

    if (user_response == "-1") break;

    // Make the request.
    user_request = new IngredientRequest(user_response, API_key);
    user_request->form_URL();

    cout << "Formed URL: " << user_request->get_URL() << endl;

    ing_result = user_request->make_request();
    cout << "\tIngredient name: " << ing_result->get_ingredient_name() << endl;
    cout << "\tcalories: " << ing_result->get_calories() << endl;
    cout << "\tcarbs: " << ing_result->get_carbs() << endl;
    cout << "\tfat: " << ing_result->get_fat() << endl;
    cout << "\tprotein: " << ing_result->get_protein() << endl;
    
  }

  cout << "Now exiting the UPC CLI" << endl;
}