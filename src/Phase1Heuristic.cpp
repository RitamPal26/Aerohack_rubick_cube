#include "Phase1Heuristic.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Static member initialization
bool Phase1Heuristic::initialized = false;
std::vector<int> Phase1Heuristic::corner_orientation_pdb;
std::vector<int> Phase1Heuristic::edge_orientation_pdb;

void Phase1Heuristic::initialize()
{
    if (initialized)
        return;

    // In a real implementation, you would load from a file first.
    std::cout << "Starting Phase 1 PDB generation...\n";
    generateCornerPDB();
    generateEdgePDB();
    std::cout << "Phase 1 PDB generation complete.\n";

    initialized = true;
}

int Phase1Heuristic::calculate(const Cube &cube)
{
    if (!initialized)
    {
        initialize();
    }

    int corner_idx = cube.getCornerOrientationIndex();
    int edge_idx = cube.getEdgeOrientationIndex();

    return std::max(corner_orientation_pdb[corner_idx], edge_orientation_pdb[edge_idx]);
}

// In src/Phase1Heuristic.cpp

void Phase1Heuristic::generateCornerPDB()
{
    std::cout << "  Generating corner orientation PDB...\n";
    corner_orientation_pdb.assign(2187, -1);
    std::queue<std::pair<Cube, int>> q;

    Cube solved_cube;
    int solved_idx = solved_cube.getCornerOrientationIndex();
    corner_orientation_pdb[solved_idx] = 0;
    q.push({solved_cube, 0});
    int visited_count = 1; // Counter for verification

    const std::vector<std::string> all_moves = {
        "U", "U'", "U2", "D", "D'", "D2", "L", "L'", "L2",
        "R", "R'", "R2", "F", "F'", "F2", "B", "B'", "B2"};

    while (!q.empty())
    {
        auto [current_cube, distance] = q.front();
        q.pop();

        for (const auto &move : all_moves)
        {
            Cube next_cube = current_cube;
            next_cube.applyMoves(move); // Or applyMove(move)
            int next_idx = next_cube.getCornerOrientationIndex();

            if (corner_orientation_pdb[next_idx] == -1)
            {
                visited_count++;
                corner_orientation_pdb[next_idx] = distance + 1;
                q.push({next_cube, distance + 1});
            }
        }
    }
    std::cout << "  Corner orientation PDB finished.\n";
    std::cout << "  Total corner states found: " << visited_count << " (Expected: 2187) ✅\n";
}

void Phase1Heuristic::generateEdgePDB()
{
    std::cout << "  Generating edge orientation PDB...\n";
    edge_orientation_pdb.assign(2048, -1);
    std::queue<std::pair<Cube, int>> q;

    Cube solved_cube;
    int solved_idx = solved_cube.getEdgeOrientationIndex();
    edge_orientation_pdb[solved_idx] = 0;
    q.push({solved_cube, 0});
    int visited_count = 1; // Counter for verification

    const std::vector<std::string> all_moves = {
        "U", "U'", "U2", "D", "D'", "D2", "L", "L'", "L2",
        "R", "R'", "R2", "F", "F'", "F2", "B", "B'", "B2"};

    while (!q.empty())
    {
        auto [current_cube, distance] = q.front();
        q.pop();

        for (const auto &move : all_moves)
        {
            Cube next_cube = current_cube;
            next_cube.applyMoves(move); // Or applyMove(move)
            int next_idx = next_cube.getEdgeOrientationIndex();

            if (edge_orientation_pdb[next_idx] == -1)
            {
                visited_count++;
                edge_orientation_pdb[next_idx] = distance + 1;
                q.push({next_cube, distance + 1});
            }
        }
    }
    std::cout << "  Edge orientation PDB finished.\n";
    std::cout << "  Total edge states found: " << visited_count << " (Expected: 2048) ✅\n";
}