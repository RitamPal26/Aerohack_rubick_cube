#include <iostream>
#include "Cube.h"
#include "IDASolver.h"

int main() {
    std::cout << "=== Quick Solver Test ===" << std::endl;
    
    Cube cube;
    
    // Simple scramble
    std::string scramble = "R U R' U'";
    std::cout << "Scramble: " << scramble << std::endl;
    cube.applyMoves(scramble);
    
    std::cout << "Scrambled: " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    // Try to solve
    IDASolver solver;
    std::string solution = solver.solve(cube);
    
    std::cout << "Solution: " << solution << std::endl;
    std::cout << "Solution length: " << solution.length() << std::endl;
    
    // Apply solution
    cube.applyMoves(solution);
    std::cout << "Final: " << (cube.isSolved() ? "SOLVED ✓" : "NOT SOLVED ✗") << std::endl;
    
    return 0;
}
