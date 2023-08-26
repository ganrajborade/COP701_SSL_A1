#!/bin/bash

# Compile the project using the Makefile
make

# Run the compiled output with user-provided arguments
./output "$1" "$2"

# Clean up generated files
make clean