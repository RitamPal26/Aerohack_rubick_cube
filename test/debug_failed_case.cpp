#include "src/Cube.h"
#include "src/IDASolver.h"
#include <iostream>

int main() {
    std::cout << "=== Debugging Failed Case ===" << std::endl;
    
    Cube cube;
    std::string scramble = "F R U' R' F' R U R'";
    cube.applyMoves(scramble);
    
    std::cout << "After scramble:" << std::endl;
    std::cout << "  Corner perm: " << cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm: " << cube.getEdgePermutationIndex() << std::endl;
    std::cout << "  Is in G1: " << (cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Is solved: " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    // Print actual edge and corner arrays
    std::cout << "\nCorner permutation: ";
    for (int i = 0; i < 8; i++) std::cout << cube.cp[i] << " ";
    std::cout << "\nCorner orientation: ";
    for (int i = 0; i < 8; i++) std::cout << cube.co[i] << " ";
    std::cout << "\nEdge permutation: ";
    for (int i = 0; i < 12; i++) std::cout << cube.ep[i] << " ";
    std::cout << "\nEdge orientation: ";
    for (int i = 0; i < 12; i++) std::cout << cube.eo[i] << " ";
    std::cout << std::endl;
    
    IDASolver solver;
    std::string solution = solver.solve(cube);
    std::cout << "\nSolution: " << solution << std::endl;
    
    // Apply solution and check final state
    cube.applyMoves(solution);
    std::cout << "\nAfter applying solution:" << std::endl;
    std::cout << "  Corner perm: " << cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm: " << cube.getEdgePermutationIndex() << std::endl;
    std::cout << "  Is in G1: " << (cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Is solved: " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    
    std::cout << "\nFinal corner permutation: ";
    for (int i = 0; i < 8; i++) std::cout << cube.cp[i] << " ";
    std::cout << "\nFinal corner orientation: ";
    for (int i = 0; i < 8; i++) std::cout << cube.co[i] << " ";
    std::cout << "\nFinal edge permutation: ";
    for (int i = 0; i < 12; i++) std::cout << cube.ep[i] << " ";
    std::cout << "\nFinal edge orientation: ";
    for (int i = 0; i < 12; i++) std::cout << cube.eo[i] << " ";
    std::cout << std::endl;
    
    // Check what a truly solved cube looks like
    std::cout << "\nFor comparison, a truly solved cube:" << std::endl;
    Cube solved;
    std::cout << "Solved corner permutation: ";
    for (int i = 0; i < 8; i++) std::cout << solved.cp[i] << " ";
    std::cout << "\nSolved edge permutation: ";
    for (int i = 0; i < 12; i++) std::cout << solved.ep[i] << " ";
    std::cout << std::endl;
    
    return 0;
}
