#include "src/Cube.h"
#include "src/IDASolver.h"
#include <iostream>

int main() {
    std::cout << "=== Phase Analysis Test ===" << std::endl;
    
    // Create and scramble a cube
    Cube cube;
    std::string scramble = "F U' R L' D B' U R";
    std::cout << "Scrambling with: " << scramble << std::endl;
    cube.applyMoves(scramble);
    
    std::cout << "After scramble:" << std::endl;
    std::cout << "  Is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    std::cout << "  Is in G1? " << (cube.isInG1() ? "YES" : "NO") << std::endl;
    
    // Let's manually test if we can get to G1 with a simple move sequence
    // Try applying some moves to see if we can reach G1
    std::cout << "\nTesting some moves to reach G1..." << std::endl;
    Cube test_cube = cube;
    std::vector<std::string> simple_moves = {"U", "D", "L2", "R2", "F2", "B2"};
    
    for (const auto& move : simple_moves) {
        test_cube.applyMoves(move);
        std::cout << "After " << move << ": In G1? " << (test_cube.isInG1() ? "YES" : "NO") << std::endl;
        if (test_cube.isInG1()) {
            std::cout << "  Found G1 state! Is solved? " << (test_cube.isSolved() ? "YES" : "NO") << std::endl;
            break;
        }
    }
    
    return 0;
}
