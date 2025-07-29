#include "src/Cube.h"
#include <iostream>

int main() {
    std::cout << "=== Simple Cube Test ===" << std::endl;
    
    // Test 1: Create a solved cube
    Cube cube;
    std::cout << "1. Created cube, is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    // Test 2: Apply a simple move and reverse it
    std::cout << "2. Applying move 'R'..." << std::endl;
    cube.applyMoves("R");
    std::cout << "   After R, is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    std::cout << "3. Applying move 'R''..." << std::endl;
    cube.applyMoves("R'");
    std::cout << "   After R', is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    // Test 3: Apply the exact scramble from main
    Cube cube2;
    std::string scramble = "F U' R L' D B' U R";
    std::cout << "4. Applying scramble: " << scramble << std::endl;
    cube2.applyMoves(scramble);
    std::cout << "   After scramble, is solved? " << (cube2.isSolved() ? "YES" : "NO") << std::endl;
    
    // Test 4: Apply the reverse scramble
    std::string reverse_scramble = "R' U' B D' L R' U F'";
    std::cout << "5. Applying reverse scramble: " << reverse_scramble << std::endl;
    cube2.applyMoves(reverse_scramble);
    std::cout << "   After reverse, is solved? " << (cube2.isSolved() ? "YES" : "NO") << std::endl;
    
    return 0;
}
