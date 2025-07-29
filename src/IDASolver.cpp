#include "IDASolver.h"
#include "Cube.h"
#include "Phase1Heuristic.h"
#include "Phase2Heuristic.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <numeric>

// Helper to get the inverse of a move
std::string get_inverse(const std::string &move)
{
    if (move.length() == 1)
        return move + "'";
    if (move[1] == '\'')
        return move.substr(0, 1);
    return move;
}

IDASolver::IDASolver()
    : corner_pdb("corner_pdb.dat") // ← this will load (or generate+save on first run)
{
}

// --- The Main Orchestrator ---
std::string IDASolver::solve(Cube start_state)
{
    // --- Phase 1 ---
    std::cout << "--- Starting Phase 1 ---" << std::endl;
    Phase1Heuristic::initialize();
    std::vector<std::string> path1;
    int threshold1 = Phase1Heuristic::calculate(start_state);
    
    // Keep a copy for Phase 1 search (will be modified during search)
    Cube phase1_cube = start_state;
    
    while (true)
    {
        std::cout << "Trying Phase 1 threshold: " << threshold1 << std::endl;
        if (search_phase1(phase1_cube, 0, threshold1, path1))
            break;
        if (threshold1 > 20)
            return "No solution found in Phase 1.";
        threshold1++;
        // Reset the cube for the next iteration
        phase1_cube = start_state;
        path1.clear();
    }

    // --- Phase 2 ---
    std::cout << "\n--- Starting Phase 2 ---" << std::endl;
    // Apply Phase 1 solution to get the proper Phase 2 starting state
    Cube phase2_start_state = start_state;
    for (const auto &move : path1) {
        phase2_start_state.applyMoves(move);
    }
    
    // Verify we're in G1
    if (!phase2_start_state.isInG1()) {
        return "Error: Phase 1 solution does not lead to G1 state.";
    }

    Phase2Heuristic::initialize();
    std::vector<std::string> path2;
    int initial_c_perm = phase2_start_state.getCornerPermutationIndex();
    int initial_e_perm = phase2_start_state.getEdgePermutationIndex();
    int threshold2 = Phase2Heuristic::calculate(initial_c_perm, initial_e_perm);
    while (true)
    {
        std::cout << "Trying Phase 2 threshold: " << threshold2 << std::endl;
        if (search_phase2(initial_c_perm, initial_e_perm, 0, threshold2, path2))
            break;
        if (threshold2 > 20)
            return "No solution found in Phase 2.";
        threshold2++;
        path2.clear();
    }

    // --- Combine Paths ---
    std::string solution_str = "";
    for (const auto &move : path1)
        solution_str += move + " ";
    for (const auto &move : path2)
        solution_str += move + " ";
    
    // --- Verify Solution ---
    std::cout << "\n--- Verifying Solution ---" << std::endl;
    Cube verify_cube = start_state;
    for (const auto &move : path1) {
        verify_cube.applyMoves(move);
    }
    for (const auto &move : path2) {
        verify_cube.applyMoves(move);
    }
    
    if (!verify_cube.isSolved()) {
        std::cout << "ERROR: Solution verification failed!" << std::endl;
        std::cout << "Final cube state:" << std::endl;
        verify_cube.print();
        return "Solution verification failed - cube not solved.";
    } else {
        std::cout << "Solution verified successfully!" << std::endl;
    }
    
    return solution_str;
}

// --- Search Functions for Each Phase ---

// Phase 1 search works on the Cube object directly
bool IDASolver::search_phase1(Cube &cube, int g, int threshold, std::vector<std::string> &path)
{
    int h = Phase1Heuristic::calculate(cube);
    if (g + h > threshold)
        return false;
    if (cube.isInG1())
        return true;

    const std::vector<std::string> moves = {"U", "D", "L", "R", "F", "B", "U2", "D2", "L2", "R2", "F2", "B2", "U'", "D'", "L'", "R'", "F'", "B'"};
    for (const auto &move : moves)
    {
        cube.applyMoves(move);
        path.push_back(move);
        if (search_phase1(cube, g + 1, threshold, path))
            return true;
        path.pop_back();
        cube.applyMoves(get_inverse(move));
    }
    return false;
}

// Phase 2 search works with indices and move tables for high speed
bool IDASolver::search_phase2(int c_perm, int e_perm, int g, int threshold, std::vector<std::string> &path)
{
    int h = Phase2Heuristic::calculate(c_perm, e_perm);
    if (g + h > threshold)
        return false;
    
    // Only consider solved when BOTH corner and edge permutations are 0
    if (c_perm == 0 && e_perm == 0)
        return true;

    const std::vector<std::string> moves = {"U", "U2", "U'", "D", "D2", "D'", "F2", "B2", "L2", "R2"};
    for (size_t i = 0; i < moves.size(); ++i)
    {
        int next_c_perm = Phase2Heuristic::corner_move_table[c_perm][i];
        int next_e_perm = Phase2Heuristic::edge_move_table[e_perm][i];
        path.push_back(moves[i]);
        if (search_phase2(next_c_perm, next_e_perm, g + 1, threshold, path))
            return true;
        path.pop_back();
    }
    return false;
}