#include "src/Cube.h"
#include "src/IDASolver.h"
#include <iostream>

int main() {
    std::cout << "=== Testing Multiple Scrambles ===" << std::endl;
    
    // Test different scramble patterns
    std::vector<std::string> test_scrambles = {
        "R U R' U'",                          // Simple 4-move scramble
        "R U R' U R U2 R'",                   // Classic algorithm
        "F R U' R' F' R U R'",                // Another common pattern
        "R U R' F' R U R' U' R' F R2 U' R'",  // More complex
        "D L2 F2 R2 D R2 U' L2 U L2 B' U L' B R' F' L F U2", // Random 19-move
        "U2 R2 F2 U2 R2 D2 L2 U2 F2 R2"     // All double moves
    };
    
    IDASolver solver;
    
    for (size_t i = 0; i < test_scrambles.size(); i++) {
        std::cout << "\n--- Test " << (i+1) << " ---" << std::endl;
        std::cout << "Scramble: " << test_scrambles[i] << std::endl;
        
        Cube cube;
        cube.applyMoves(test_scrambles[i]);
        
        std::cout << "Is scrambled cube in G1? " << (cube.isInG1() ? "YES" : "NO") << std::endl;
        std::cout << "Is scrambled cube solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
        
        // Solve it
        std::string solution = solver.solve(cube);
        std::cout << "Solution: " << solution << std::endl;
        std::cout << "Solution length: " << solution.length() << " characters" << std::endl;
        
        // Verify solution
        Cube test_cube = cube;
        test_cube.applyMoves(solution);
        
        if (test_cube.isSolved()) {
            std::cout << "✅ VERIFICATION PASSED: Cube is solved!" << std::endl;
        } else {
            std::cout << "❌ VERIFICATION FAILED: Cube is NOT solved!" << std::endl;
            std::cout << "   Final state - In G1? " << (test_cube.isInG1() ? "YES" : "NO") << std::endl;
            std::cout << "   Corner perm: " << test_cube.getCornerPermutationIndex() << std::endl;
            std::cout << "   Edge perm: " << test_cube.getEdgePermutationIndex() << std::endl;
            break; // Stop testing if we find a failure
        }
    }
    
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Test already solved cube
    std::cout << "\nTesting already solved cube:" << std::endl;
    Cube solved_cube;
    std::string solution_solved = solver.solve(solved_cube);
    std::cout << "Solution for solved cube: '" << solution_solved << "'" << std::endl;
    
    // Test a cube that's only one move away from solved
    std::cout << "\nTesting cube one move from solved:" << std::endl;
    Cube one_move_cube;
    one_move_cube.applyMoves("R");
    std::string solution_one = solver.solve(one_move_cube);
    std::cout << "Solution for R scramble: " << solution_one << std::endl;
    
    Cube verify_one = one_move_cube;
    verify_one.applyMoves(solution_one);
    std::cout << "One-move verification: " << (verify_one.isSolved() ? "✅ PASSED" : "❌ FAILED") << std::endl;
    
    return 0;
}
