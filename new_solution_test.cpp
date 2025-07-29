#include "src/Cube.h"
#include <iostream>

int main() {
    std::cout << "=== New Solution Test ===" << std::endl;
    
    // Test the new solution
    Cube cube;
    cube.applyMoves("F U' R L' D B' U R");
    std::string new_solution = "U F L2 B R F2 U2 B F2 U B2 F2 U F2 D F2 U2 F2 U D'";
    std::cout << "Applying new solution: " << new_solution << std::endl;
    cube.applyMoves(new_solution);
    
    std::cout << "After new solution:" << std::endl;
    std::cout << "  Is solved: " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    std::cout << "  Is in G1: " << (cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Corner perm index: " << cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm index: " << cube.getEdgePermutationIndex() << std::endl;
    
    // Check what the edge permutation looks like
    std::cout << "\nEdge permutation array: ";
    for (int i = 0; i < 12; i++) {
        std::cout << cube.ep[i] << " ";
    }
    std::cout << std::endl;
    
    // Check specifically edges 8-11
    std::cout << "Edges 8-11: ";
    for (int i = 8; i < 12; i++) {
        std::cout << cube.ep[i] << " ";
    }
    std::cout << "(should be: 8 9 10 11)" << std::endl;
    
    return 0;
}
