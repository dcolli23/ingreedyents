#include "UPC_CLI.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

int main () {
  UPC_CLI my_cli = UPC_CLI();
  my_cli.start_CLI();
  return 0;
}