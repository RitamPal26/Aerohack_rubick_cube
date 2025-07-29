#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "Cube.h"
#include "IDASolver.h"

void generateExampleOutput(const std::string &filename, const std::string &content) {
    std::ofstream file("examples/" + filename);
    if (file.is_open()) {
        file << content;
        file.close();
        std::cout << "Generated example: examples/" << filename << std::endl;
    } else {
        std::cout << "Error: Could not create examples/" << filename << std::endl;
    }
}

std::string cubeStateToString(const Cube& cube) {
    std::string result = "";
    std::array<int, 54> state = cube.getState();
    const char *face_names[] = {"Up", "Right", "Front", "Down", "Left", "Back"};
    const char color_letters[] = {'W', 'Y', 'G', 'B', 'O', 'R'};
    
    for (int face = 0; face < 6; face++) {
        result += face_names[face] + std::string(":\n");
        for (int row = 0; row < 3; row++) {
            result += "  ";
            for (int col = 0; col < 3; col++) {
                int pos = face * 9 + row * 3 + col;
                result += color_letters[state[pos]];
                result += " ";
            }
            result += "\n";
        }
    }
    return result;
}

void generateDetailedExample(int exampleNum, const std::string& scramble, IDASolver& solver) {
    std::string folder = "ex" + std::to_string(exampleNum);
    std::string content = "";
    
    content += "=== EXAMPLE " + std::to_string(exampleNum) + " - COMPLETE SOLUTION WALKTHROUGH ===\n\n";
    
    // Create scrambled cube
    Cube cube;
    content += "1. INITIAL SOLVED STATE:\n";
    content += cubeStateToString(cube);
    content += "Cube state: SOLVED\n\n";
    
    // Apply scramble
    cube.applyMoves(scramble);
    content += "2. SCRAMBLE APPLIED: \"" + scramble + "\"\n";
    content += cubeStateToString(cube);
    content += "Cube state: SCRAMBLED\n";
    content += "Coordinates:\n";
    content += "  Corner Orientation: " + std::to_string(cube.getCornerOrientationIndex()) + "\n";
    content += "  Edge Orientation: " + std::to_string(cube.getEdgeOrientationIndex()) + "\n";
    content += "  Corner Permutation: " + std::to_string(cube.getCornerPermutationIndex()) + "\n";
    content += "  Edge Permutation: " + std::to_string(cube.getEdgePermutationIndex()) + "\n";
    content += "  Is in G1 subgroup: " + std::string(cube.isInG1() ? "YES" : "NO") + "\n\n";
    
    // Solve
    auto start_time = std::chrono::high_resolution_clock::now();
    std::string solution = solver.solve(cube);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    content += "3. SOLVER ANALYSIS:\n";
    if (solution.find("failed") != std::string::npos || solution.find("Error") != std::string::npos) {
        content += "Solution: FAILED\n";
        content += "Error: " + solution + "\n\n";
    } else {
        content += "Solution found: \"" + solution + "\"\n";
        content += "Solution time: " + std::to_string(duration.count()) + " ms\n";
        content += "Solution length: " + std::to_string(solution.length()) + " characters\n\n";
        
        // Apply solution and verify
        Cube solved_cube = cube;
        solved_cube.applyMoves(solution);
        
        content += "4. FINAL STATE AFTER APPLYING SOLUTION:\n";
        content += cubeStateToString(solved_cube);
        content += "Cube state: " + std::string(solved_cube.isSolved() ? "SOLVED" : "NOT SOLVED") + "\n";
        content += "Verification: " + std::string(solved_cube.isSolved() ? "PASSED" : "FAILED") + "\n\n";
        
        content += "5. SUMMARY:\n";
        content += "  Scramble: " + scramble + "\n";
        content += "  Solution: " + solution + "\n";
        content += "  Total moves in solution: " + std::to_string(solution.length()) + " characters\n";
        content += "  Solving time: " + std::to_string(duration.count()) + " ms\n";
        content += "  Result: " + std::string(solved_cube.isSolved() ? "SUCCESS" : "FAILED") + "\n";
    }
    
    // Write to file
    std::ofstream file("examples/" + folder + "/complete_solution.txt");
    if (file.is_open()) {
        file << content;
        file.close();
        std::cout << "Generated detailed example: examples/" << folder << "/complete_solution.txt" << std::endl;
    }
}

int main()
{
    std::cout << "Creating a 3x3x3 Rubik's Cube." << std::endl;
    std::cout << "Generating output examples in ./examples/ folder..." << std::endl;

    IDASolver solver;

    // Generate detailed examples with complete cube states
    std::cout << "\n--- Generating Detailed Examples ---" << std::endl;
    
    std::vector<std::string> detailed_scrambles = {
        "R U R' U'",                    // Simple 4-move sequence
        "F R U' R' F'",                 // T-permutation setup  
        "R U2 R' D' R U' R' D",        // Complex 8-move sequence
        "U R U' L' U R' U' L"          // Cross-pattern sequence
    };
    
    for (size_t i = 0; i < detailed_scrambles.size(); i++) {
        generateDetailedExample(i + 1, detailed_scrambles[i], solver);
    }

    std::cout << "\n=== Detailed example files generated in ./examples/ex1, ex2, ex3, ex4 folders ===" << std::endl;

    return 0;
}
