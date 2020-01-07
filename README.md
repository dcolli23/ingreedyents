# **ingreedyents**
 Optimizes the use of ingredients by ingredient UPC lookup combined with web scraping recipes.

# Table of Contents

+ [Overview](#overview)
+ [Language](#language)
+ [Plan of Action](#plan-of-action)
  + [Reading the UPC](#reading-the-upc)
  + [Getting the Product Information](#getting-the-product-information)
  + [Obtaining the Optimized Recipe Choices](#obtaining-the-optimized-recipe-choices)
  + [User Interface to Select Recipe](#user-interface-to-select-recipe)

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

So this is DEFINITELY doable in Python. But what if I did it in C++ to be a true glutton for punishment?

# Plan of Action
This is where I'm going to jot down my notes on my plan of attack for all of this.

## Reading the UPC

### Python

I'm looking at UPC readers and I found one on amazon that seems to support everything that I want to do. 

It seems like the way that this is going to work is by reading in the data via a USB virtual COM port. I found [this](https://stackoverflow.com/questions/2291772/virtual-serial-device-in-python) StackOverflow thread to be helpful.

I also have my old Galaxy Note 2 that I could take a whack at developing something for. That would prevent me from having to buy anything but may be a bit annoying to do.

I think the best option would be to buy a barcode reader that transmits data into a USB.

### C++

So I've found [this](https://stackoverflow.com/questions/34842163/how-to-read-from-serial-device-in-c) link which talks about reading in serial data using C++. So I think it's doable.

## Getting the Product Information

### Python

I believe this is wholly-completed with the BarcodeSpider.com API that I've signed up for and the standard Python library which is AWESOME! BUT. I don't know if I want to do the whole thing in Python yet. If we go the application route, I think I'd have to develop in Java.

### C++

I've found [this](https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c) link which discusses HTTP GET requests with C++. It seems like there are a lot of sloppy/undocumented stuff out there but that POCO might not be bad?

Wonder if I'll need rapidJSON for parsing JSONs I get from the APIs.

## Obtaining the Optimized Recipe Choices

### Python

This will likely be completed by making a request to a recipe API. Spoonacular seems to be pretty good for this. You get 150 points for free per month. Calling the endpoint costs 1 point and each recipe returned costs 0.01 points. So finding 1000 recipes would cost 11 points. HOLY MOLY they do macros and nutritional information too! This is amazing. And actually Spoonacular has the capability of reading by UPC as well. Well this is quickly becoming something I may pay for.

### C++

Basically the same as above I think? If I can get the HTTP GETs requests working in C++ this is easy peasy lemon squeazy. 

## User Interface to Select Recipe

This is where the language choice might be a huge pain in the butt. If I choose to go with a GUI for browsing the recipes and use C++ this will likely be a huge time sinkhole as I don't think there's a good free, open-source, easy-to-develop library for GUI development on Linux (which the Pi will be running).