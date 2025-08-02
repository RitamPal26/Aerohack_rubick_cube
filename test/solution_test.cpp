#include "src/Cube.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Solution Verification Test ===" << std::endl;
    
    // Create the exact same scrambled state
    Cube cube;
    std::string scramble = "F U' R L' D B' U R";
    std::cout << "1. Applying scramble: " << scramble << std::endl;
    cube.applyMoves(scramble);
    std::cout << "   After scramble, is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    // Apply the exact solution (trimmed)
    std::string solution = "U F L2 B R F2 U2 B F2 U2 L2 U F2 R2 D' R2 B2 L2 U R2";
    std::cout << "2. Applying solution: " << solution << std::endl;
    cube.applyMoves(solution);
    std::cout << "   After solution, is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    // Test if it's actually the trailing spaces causing issues
    Cube cube2;
    cube2.applyMoves(scramble);
    std::string solution_with_spaces = "U F L2 B R F2 U2 B F2 U2 L2 U F2 R2 D' R2 B2 L2 U R2   ";
    std::cout << "3. Applying solution with trailing spaces..." << std::endl;
    cube2.applyMoves(solution_with_spaces);
    std::cout << "   After solution with spaces, is solved? " << (cube2.isSolved() ? "YES" : "NO") << std::endl;
    
    return 0;
}
