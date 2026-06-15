#!/bin/bash

# Define the source file and output executable
SOURCE_FILE="./copy.cpp"
OUTPUT_FILE="copy.exe"

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
