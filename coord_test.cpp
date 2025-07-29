#include "src/Cube.h"
#include <iostream>

int main() {
    std::cout << "=== Coordinate System Test ===" << std::endl;
    
    // Test a solved cube
    Cube solved_cube;
    std::cout << "Solved cube:" << std::endl;
    std::cout << "  Is solved: " << (solved_cube.isSolved() ? "YES" : "NO") << std::endl;
    std::cout << "  Is in G1: " << (solved_cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Corner perm index: " << solved_cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm index: " << solved_cube.getEdgePermutationIndex() << std::endl;
    
    // Test the scrambled and then solved state
    std::cout << "\nScramble and apply our solution:" << std::endl;
    Cube test_cube;
    test_cube.applyMoves("F U' R L' D B' U R");
    std::string solution = "U F L2 B R F2 U2 B F2 U2 L2 U F2 R2 D' R2 B2 L2 U R2";
    test_cube.applyMoves(solution);
    
    std::cout << "  Is solved: " << (test_cube.isSolved() ? "YES" : "NO") << std::endl;
    std::cout << "  Is in G1: " << (test_cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Corner perm index: " << test_cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm index: " << test_cube.getEdgePermutationIndex() << std::endl;
    
    // Test just the Phase 1 portion
    std::cout << "\nJust after Phase 1 (should be in G1):" << std::endl;
    Cube phase1_cube;
    phase1_cube.applyMoves("F U' R L' D B' U R");
    phase1_cube.applyMoves("U F L2 B R F2 U2 B");  // Just the Phase 1 part
    
    std::cout << "  Is solved: " << (phase1_cube.isSolved() ? "YES" : "NO") << std::endl;
    std::cout << "  Is in G1: " << (phase1_cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Corner perm index: " << phase1_cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm index: " << phase1_cube.getEdgePermutationIndex() << std::endl;
    
    return 0;
}
