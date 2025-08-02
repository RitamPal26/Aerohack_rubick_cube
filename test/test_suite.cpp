#include "../src/Cube.h"
#include "../src/IDASolver.h"
#include <iostream>
#include <cassert>
#include <chrono>

void testBasicMoves() {
    std::cout << "Testing basic moves..." << std::endl;
    
    Cube cube;
    assert(cube.isSolved());
    
    // Test each move is reversible
    std::vector<std::string> moves = {"U", "R", "F", "D", "L", "B"};
    for (const auto& move : moves) {
        Cube test = cube;
        test.applyMoves(move);
        test.applyMoves(move + "'");
        assert(test.isSolved());
        std::cout << " " << move << " move is reversible" << std::endl;
    }
}

void testSimpleScrambles() {
    std::cout << "\nTesting simple scrambles..." << std::endl;
    
    std::vector<std::string> scrambles = {
        "R",
        "R U R' U'", 
        "F R U' R' F'"
    };
    
    IDASolver solver;
    
    for (const auto& scramble : scrambles) {
        std::cout << "Testing scramble: " << scramble << std::endl;
        
        Cube cube;
        cube.applyMoves(scramble);
        
        auto start = std::chrono::high_resolution_clock::now();
        std::string solution = solver.solve(cube);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        if (!solution.empty()) {
            // Verify solution
            Cube test = cube;
            test.applyMoves(solution);
            
            if (test.isSolved()) {
                std::cout << " PASS - Solution: " << solution 
                         << " (Time: " << duration.count() << "ms)" << std::endl;
            } else {
                std::cout << " FAIL - Solution doesn't solve cube" << std::endl;
            }
        } else {
            std::cout << " FAIL - No solution found" << std::endl;
        }
    }
}

void testCoordinateSystems() {
    std::cout << "\nTesting coordinate systems..." << std::endl;
    
    Cube solved;
    assert(solved.getCornerOrientationIndex() == 0);
    assert(solved.getEdgeOrientationIndex() == 0);
    assert(solved.getCornerPermutationIndex() == 0);
    assert(solved.getEdgePermutationIndex() == 0);
    assert(solved.isInG1());
    
    std::cout << " Solved cube has correct coordinate indices" << std::endl;
}

int main() {
    std::cout << "=== Rubik's Cube Solver Test Suite ===" << std::endl;
    
    try {
        testBasicMoves();
        testSimpleScrambles();
        testCoordinateSystems();
        
        std::cout << "\n All tests completed!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "\n Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
