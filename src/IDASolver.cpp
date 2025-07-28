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

// --- The Main Orchestrator ---
std::string IDASolver::solve(Cube start_state)
{
    // --- Phase 1 ---
    std::cout << "--- Starting Phase 1 ---" << std::endl;
    Phase1Heuristic::initialize();
    std::vector<std::string> path1;
    int threshold1 = Phase1Heuristic::calculate(start_state);
    while (true)
    {
        std::cout << "Trying Phase 1 threshold: " << threshold1 << std::endl;
        if (search_phase1(start_state, 0, threshold1, path1))
            break;
        if (threshold1 > 20)
            return "No solution found in Phase 1.";
        threshold1++;
    }

    // --- Phase 2 ---
    std::cout << "\n--- Starting Phase 2 ---" << std::endl;
    // The start_state object is now correctly positioned at the end of Phase 1.
    // We can use it directly to start Phase 2.
    Cube phase2_start_state = start_state;

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
    }

    // --- Combine Paths ---
    std::string solution_str = "";
    for (const auto &move : path1)
        solution_str += move + " ";
    for (const auto &move : path2)
        solution_str += move + " ";
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
    if (h == 0)
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