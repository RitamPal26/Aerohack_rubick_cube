#include "src/Cube.h"
#include "src/Phase1Heuristic.h"
#include <iostream>

// Simple manual Phase 1 test
bool manual_search_phase1(Cube &cube, int g, int threshold, std::vector<std::string> &path, int max_depth = 6) {
    int h = Phase1Heuristic::calculate(cube);
    if (g + h > threshold) return false;
    if (cube.isInG1()) return true;
    if (g >= max_depth) return false; // Limit depth for testing
    
    const std::vector<std::string> moves = {"U", "D", "L", "R", "F", "B", "U2", "D2", "L2", "R2", "F2", "B2", "U'", "D'", "L'", "R'", "F'", "B'"};
    for (const auto &move : moves) {
        cube.applyMoves(move);
        path.push_back(move);
        if (manual_search_phase1(cube, g + 1, threshold, path, max_depth)) return true;
        path.pop_back();
        // Apply inverse move
        if (move.length() == 1) cube.applyMoves(move + "'");
        else if (move[1] == '\'') cube.applyMoves(move.substr(0, 1));
        else cube.applyMoves(move); // U2 is its own inverse
    }
    return false;
}

int main() {
    std::cout << "=== Manual Phase 1 Test ===" << std::endl;
    
    // Initialize Phase 1 heuristic
    Phase1Heuristic::initialize();
    
    // Create and scramble a cube
    Cube cube;
    std::string scramble = "F U' R L' D B' U R";
    std::cout << "Scrambling with: " << scramble << std::endl;
    cube.applyMoves(scramble);
    
    std::cout << "After scramble:" << std::endl;
    std::cout << "  Is solved? " << (cube.isSolved() ? "YES" : "NO") << std::endl;
    std::cout << "  Is in G1? " << (cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Phase 1 heuristic: " << Phase1Heuristic::calculate(cube) << std::endl;
    
    // Try to find a Phase 1 solution
    std::vector<std::string> path1;
    int threshold = Phase1Heuristic::calculate(cube);
    bool found = false;
    
    while (!found && threshold <= 10) {
        std::cout << "Trying threshold: " << threshold << std::endl;
        path1.clear();
        found = manual_search_phase1(cube, 0, threshold, path1);
        if (!found) threshold++;
    }
    
    if (found) {
        std::cout << "Found Phase 1 solution: ";
        for (const auto& move : path1) std::cout << move << " ";
        std::cout << std::endl;
        
        // Apply the solution to verify
        Cube test_cube;
        test_cube.applyMoves(scramble);
        for (const auto& move : path1) test_cube.applyMoves(move);
        
        std::cout << "After applying Phase 1 solution:" << std::endl;
        std::cout << "  Is solved? " << (test_cube.isSolved() ? "YES" : "NO") << std::endl;
        std::cout << "  Is in G1? " << (test_cube.isInG1() ? "YES" : "NO") << std::endl;
    } else {
        std::cout << "No Phase 1 solution found within threshold 10" << std::endl;
    }
    
    return 0;
}
