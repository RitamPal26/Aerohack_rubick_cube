#include "src/Cube.h"
#include "src/IDASolver.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Final Comprehensive Test ===" << std::endl;
    
    std::vector<std::string> test_scrambles = {
        "", // Solved cube
        "R", // Simple one move
        "R U R' U'", // Simple sequence
        "F R U' R' F'", // Algorithm sequence
        "F R U' R' F' R U R'", // The problematic case that was failing
        "R U2 R' D' R U' R' D", // Another test case
    };
    
    IDASolver solver;
    int passed = 0;
    int total = test_scrambles.size();
    
    for (size_t i = 0; i < test_scrambles.size(); i++) {
        std::cout << "\n--- Test Case " << (i+1) << " ---" << std::endl;
        std::cout << "Scramble: \"" << test_scrambles[i] << "\"" << std::endl;
        
        // Create and scramble cube
        Cube cube;
        if (!test_scrambles[i].empty()) {
            cube.applyMoves(test_scrambles[i]);
        }
        
        std::cout << "Is scrambled cube solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
        
        // Solve the cube
        std::string solution = solver.solve(cube);
        
        if (solution.find("failed") != std::string::npos || solution.find("Error") != std::string::npos) {
            std::cout << "FAILED: " << solution << std::endl;
            continue;
        }
        
        std::cout << "Solution: " << solution << std::endl;
        
        // Apply solution and verify
        Cube test_cube = cube;
        test_cube.applyMoves(solution);
        
        if (test_cube.isSolved()) {
            std::cout << "PASSED: Solution verified correct." << std::endl;
            passed++;
        } else {
            std::cout << "FAILED: Solution does not solve the cube." << std::endl;
            test_cube.print();
        }
    }
    
    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "Passed: " << passed << "/" << total << std::endl;
    std::cout << "Success rate: " << (100.0 * passed / total) << "%" << std::endl;
    
    if (passed == total) {
        std::cout << "All tests PASSED! The solver is working correctly." << std::endl;
    } else {
        std::cout << "Some tests FAILED. The solver needs more debugging." << std::endl;
    }
    
    return 0;
}
