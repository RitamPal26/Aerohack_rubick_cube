@echo off
echo Building Rubik's Cube Solver...
g++ -std=c++17 -Wall -g -o rubiks_solver.exe src/*.cpp
if %ERRORLEVEL% EQU 0 (
    echo Build successful! Run with: ./rubiks_solver.exe
) else (
    echo Build failed!
)
pause
