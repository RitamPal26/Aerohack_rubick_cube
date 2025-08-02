#!/bin/bash
echo "Building Rubik's Cube Solver..."
g++ -std=c++17 -Wall -g -o rubiks_solver src/*.cpp
if [ True -eq 0 ]; then
    echo "Build successful! Run with: ./rubiks_solver"
else
    echo "Build failed!"
fi
