# **ingreedyents**
 Optimizes the use of ingredients by ingredient UPC lookup combined with web scraping recipes.

# Table of Contents

+ [Overview](#overview)
+ [Language](#language)
+ [Building](#building)
+ [Plan of Action](#plan-of-action)
  + [Reading the UPC](#reading-the-upc)
  + [Getting the Product Information](#getting-the-product-information)
  + [Obtaining the Optimized Recipe Choices](#obtaining-the-optimized-recipe-choices)
  + [User Interface to Select Recipe](#user-interface-to-select-recipe)
+ [Testing](#testing)
  + [Running Tests](#running-tests)
  + [Writing Tests](#writing-tests)

# Overview

I'm going to just jot some ideas down that I have and hopefully some organization will appear as an emergent property.

I kind of imagine this to be a handheld device that sends (likely via bluetooth) the UPC information (or whatever is read in by the device) to a raspberry pi which then does the processing (or a request for the processing).

This is a good link for food APIs [https://www.quora.com/Are-there-any-free-APIs-for-food-recipes](https://www.quora.com/Are-there-any-free-APIs-for-food-recipes).

This project will break down into several parts:

1. Actually getting the UPC into a usable format. This could be in the form of a data packet that's passed between programs or as a string that is used within the same program.
2. Getting the product information.
3. Obtaining the optimized recipe choices.
4. User interface to select the recipe.

So I know I can do all of the above in Python except for #1. I'm not sure how to go about doing number 1 in python. Perhaps that's worth a google.
+ This is a good resource showing how to do exactly what I want to do with a raspberry pi [https://www.pyimagesearch.com/2018/05/21/an-opencv-barcode-and-qr-code-scanner-with-zbar/](https://www.pyimagesearch.com/2018/05/21/an-opencv-barcode-and-qr-code-scanner-with-zbar/).

# Language

I've chosen to do this in C++. It's a fun project and will be a good challenge for me. I can also try and implement a barcode scanner using OpenCV with C++, so that will be really fun.

# Building

Ingreedyents is built using CMake. To build ingreedyents and run all tests, type the following in a terminal while in the root directory of the repository:

```
rm -rf build
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
./test_main
```

CMake will automatically pull the `googletest` framework for you. Alternatively, you can run:

```
./run_tests.sh
```

In the root of the repository.

If you would like to build ingreedyents without running tests, type the following in a terminal while in the root directory of the repository:

```
rm -rf build
mkdir build && cd build
cmake -DBUILD_TESTS=OFF ..
make
```

Alternatively, you can run:

```
./build_app_no_tests.sh
```

# Plan of Action
This is where I'm going to jot down my notes on my plan of attack for all of this.

## Reading the UPC

I'm looking at UPC readers and I found one on amazon that seems to support everything that I want to do. 

It seems like the way that this is going to work is by reading in the data via a USB virtual COM port. I found [this](https://stackoverflow.com/questions/2291772/virtual-serial-device-in-python) StackOverflow thread to be helpful.

I also have my old Galaxy Note 2 that I could take a whack at developing something for. That would prevent me from having to buy anything but may be a bit annoying to do.

I think the best option would be to buy a barcode reader that transmits data into a USB.

So I've found [this](https://stackoverflow.com/questions/34842163/how-to-read-from-serial-device-in-c) link which talks about reading in serial data using C++. So I think it's doable.

## Getting the Product Information

I should form some sort of cache for the UPCs that I have read such that when I scan an item, it searches the cached UPCs first before making the HTTP request. This way it will not cost me points when I scan items that I have scanned in the past.

I believe this is wholly-completed with the spoonacular API that I've signed up for. This will be accomplished with a GET request which can be done via the `HTTPRequest` library I've downloaded.
  + Spoonacular has a good example of what this will look like here: https://spoonacular.com/food-api/docs#Search-Grocery-Products-by-UPC

I'm going to use RapidJSON to parse the JSON-formatted strings that I get from the GET requests.
  + I'm planning on making a class for this to distill down all of the information I'm going to get in the returned JSON file. 

## Obtaining the Optimized Recipe Choices

This will likely be completed by making a request to a recipe API. Spoonacular seems to be pretty good for this. You get 150 points for free per month. Calling the endpoint costs 1 point and each recipe returned costs 0.01 points. So finding 1000 recipes would cost 11 points. HOLY MOLY they do macros and nutritional information too! This is amazing. And actually Spoonacular has the capability of reading by UPC as well. Well this is quickly becoming something I may pay for.

## User Interface to Select Recipe

I've done some research on developing using the Qt framework and it seems to be easy enough. I'm likely going to choose this.

# Testing

## Running Tests

To build and run all tests, simply execute `./run_tests.sh` in the repository's root directory.

## Writing Tests

This project uses the `googletest` framework for testing functionality. This is the process for writing a new test suite.

Note: Test suite is used to refer to a new group of tests indepenedent from other tests. In this repository, we're making a new header file for each test suite and writing a new test suite for each class.

1. Make a new `.h` file in the `/tests/include` directory of the repository. Name it the name of the test suite.
2. In the new `<test_suite>.h` file, write the following as boilerplate:
    ```c++
    #include "<name_of_class_under_test>"
    #include "gtest/gtest.h"

    // insert any test fixtures here.

    TEST(<test_suite_name>, <test_name>) {
      // insert code for test here using:
      //    ASSERT_*(x, y) when you want the test to halt on failure.
      //    EXPECT_*(x, y) when you want the test to continue upon failure.
    }
    ```
3. Write the first test that you would like.
4. In `tests/main.cpp`, `include` your new test suite header file.


