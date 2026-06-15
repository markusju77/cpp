#!/bin/bash

# Define the source file and output executable
SOURCE_FILE="./src/asm_ba.cpp ./src/infix_to_postfix.cpp ./src/karnaugh.cpp ./src/quine_mccluskell.cpp"
OUTPUT_FILE="./bin/asm_ba.exe"

# Use pkg-config to get the necessary flags for a library, e.g., gtk+-3.0
PKG_FLAGS=$(pkg-config --cflags --libs gtk+-3.0)

# Compile the source file with g++
g++ $SOURCE_FILE -o $OUTPUT_FILE $PKG_FLAGS

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable created: $OUTPUT_FILE"
else
    echo "Compilation failed."
fi




 #g++ `pkg-config --cflags gtk+-3.0` -o asm_ba ./src/asm_ba.cpp ./src/infix_to_postfix.cpp ./src/karnaugh.cpp ./src/quine_mccluskell.cpp `pkg-config --libs gtk+-3.0`
