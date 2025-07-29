#include <iostream>
#include "Cube.h"

int main() {
    std::cout << "=== Move Validation Test ===" << std::endl;
    
    Cube cube;
    
    // Test each move is reversible
    std::vector<std::string> moves = {"R", "L", "U", "D", "F", "B"};
    
    for (const auto& move : moves) {
        Cube test_cube;
        test_cube.applyMoves(move);
        test_cube.applyMoves(move + "'");
        
        std::cout << move << ": " << (test_cube.isSolved() ? "✓ PASS" : "✗ FAIL") << std::endl;
    }
    
    std::cout << "\n=== Complex Sequence Test ===" << std::endl;
    
    // Test a more complex sequence
    std::string sequence = "R U R' F R F' U F U' F'";
    std::cout << "Applying: " << sequence << std::endl;
    
    cube.applyMoves(sequence);
    std::cout << "Cube solved after sequence: " << (cube.isSolved() ? "YES (this sequence returns to solved)" : "NO (expected - sequence should scramble)") << std::endl;
    
    return 0;
}
