# Stock Market Order Matching Simulator

A C++ program that simulates how buy and sell orders are processed in a simplified stock market.

The program reads orders from an input file, stores pending buy and sell orders, matches compatible orders based on price and arrival priority, executes trades, and writes the results to an output file.

## Features

- Processes buy and sell orders from text files
- Supports limit orders and market orders
- Matches orders using priority rules:
  - Market orders have the highest priority
  - Higher buy prices have higher priority
  - Lower sell prices have higher priority
  - Earlier orders are prioritised when prices are equal
- Handles partial order execution
- Tracks the latest trading price
- Writes executed and unexecuted orders to output files
- Uses a Makefile for compilation

## Technologies Used

- C++
- STL containers
- File handling
- Makefile
- Object-oriented programming

## Project Structure


.
├── main.cpp
├── Market.cpp
├── Market.h
├── Order.cpp
├── Order.h
├── Makefile
├── input1.txt
├── input2.txt
├── ...
└── input10.txt

## How to Compile and Run

Make sure you have a C++ compiler and `make` installed.

To compile the project, run:


make

This will create an executable file called:

main

To run the program, provide one of the input files  command-line argument:

./main input1.txt

The program will process the orders from the input file and generate the output file, such as:

output1.txt
