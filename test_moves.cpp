#include <iostream>
#include "Cube.h"

int main() {
    std::cout << "=== Simple Move Test ===" << std::endl;
    
    // Test a single R move
    Cube cube;
    std::cout << "Initial cube state (should be solved): " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    std::cout << "\nApplying R move..." << std::endl;
    cube.applyMoves("R");
    std::cout << "After R: " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    std::cout << "\nApplying R' move..." << std::endl;
    cube.applyMoves("R'");
    std::cout << "After R R': " << (cube.isSolved() ? "SOLVED" : "NOT SOLVED") << std::endl;
    
    if (!cube.isSolved()) {
        std::cout << "\nDEBUG: Corner permutation: ";
        for (int i = 0; i < 8; i++) {
            std::cout << cube.cp[i] << " ";
        }
        std::cout << "\nDEBUG: Corner orientation: ";
        for (int i = 0; i < 8; i++) {
            std::cout << cube.co[i] << " ";
        }
        std::cout << "\nDEBUG: Edge permutation: ";
        for (int i = 0; i < 12; i++) {
            std::cout << cube.ep[i] << " ";
        }
        std::cout << "\nDEBUG: Edge orientation: ";
        for (int i = 0; i < 12; i++) {
            std::cout << cube.eo[i] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
