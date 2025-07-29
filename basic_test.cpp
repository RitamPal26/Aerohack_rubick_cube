#include <iostream>
#include "Cube.h"

int main() {
    std::cout << "=== Simple Scramble-Unscramble Test ===" << std::endl;
    
    Cube cube;
    std::cout << "1. Initial: " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    // Apply a simple scramble
    std::string scramble = "R U R' U'";
    std::cout << "2. Applying scramble: " << scramble << std::endl;
    cube.applyMoves(scramble);
    std::cout << "   After scramble: " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    // Apply the inverse to unscramble  
    std::string unscramble = "U R U' R'";
    std::cout << "3. Applying unscramble: " << unscramble << std::endl;
    cube.applyMoves(unscramble);
    std::cout << "   After unscramble: " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    if (!cube.isSolved()) {
        std::cout << "ERROR: Manual unscramble failed! Move implementation still has issues." << std::endl;
        return 1;
    }
    
    std::cout << "SUCCESS: Basic move sequences work correctly!" << std::endl;
    return 0;
}
