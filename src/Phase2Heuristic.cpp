#include "Phase2Heuristic.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // For std::max

// Static member initialization
bool Phase2Heuristic::initialized = false;
std::vector<int> Phase2Heuristic::corner_permutation_pdb;
std::vector<int> Phase2Heuristic::edge_permutation_pdb;
std::vector<std::vector<int>> Phase2Heuristic::corner_move_table;
std::vector<std::vector<int>> Phase2Heuristic::edge_move_table;

// This is the single, correct generation function.
void Phase2Heuristic::generatePDBsAndMoveTables()
{
    const std::vector<std::string> moves = {"U", "U2", "U'", "D", "D2", "D'", "F2", "B2", "L2", "R2"};

    // --- Corners ---
    std::cout << "  Generating corner permutation PDB and move table...\n  Progress: ";
    corner_permutation_pdb.assign(40320, -1);
    corner_move_table.assign(40320, std::vector<int>(moves.size()));
    std::queue<Cube> q_c;

    Cube solved_c;
    corner_permutation_pdb[0] = 0;
    q_c.push(solved_c);
    int count_c = 1;

    while (!q_c.empty())
    {
        Cube current_cube = q_c.front();
        q_c.pop();
        int current_idx = current_cube.getCornerPermutationIndex();

        for (size_t i = 0; i < moves.size(); ++i)
        {
            Cube next_cube = current_cube;
            next_cube.applyMoves(moves[i]);
            int next_idx = next_cube.getCornerPermutationIndex();

            corner_move_table[current_idx][i] = next_idx;

            if (corner_permutation_pdb[next_idx] == -1)
            {
                corner_permutation_pdb[next_idx] = corner_permutation_pdb[current_idx] + 1;
                q_c.push(next_cube);
                count_c++;
                if (count_c % 4032 == 0)
                    std::cout << "." << std::flush;
            }
        }
    }
    std::cout << " Done.\n";

    // --- Edges ---
    std::cout << "  Generating edge permutation PDB and move table...\n  Progress: ";
    edge_permutation_pdb.assign(40320, -1);
    edge_move_table.assign(40320, std::vector<int>(moves.size()));
    std::queue<Cube> q_e;

    Cube solved_e;
    edge_permutation_pdb[0] = 0;
    q_e.push(solved_e);
    int count_e = 1;

    while (!q_e.empty())
    {
        Cube current_cube = q_e.front();
        q_e.pop();
        int current_idx = current_cube.getEdgePermutationIndex();

        for (size_t i = 0; i < moves.size(); ++i)
        {
            Cube next_cube = current_cube;
            next_cube.applyMoves(moves[i]);
            int next_idx = next_cube.getEdgePermutationIndex();

            edge_move_table[current_idx][i] = next_idx;

            if (edge_permutation_pdb[next_idx] == -1)
            {
                edge_permutation_pdb[next_idx] = edge_permutation_pdb[current_idx] + 1;
                q_e.push(next_cube);
                count_e++;
                if (count_e % 4032 == 0)
                    std::cout << "." << std::flush;
            }
        }
    }
    std::cout << " Done.\n";
}

void Phase2Heuristic::initialize()
{
    if (initialized)
        return;
    std::cout << "Starting Phase 2 PDB and Move Table generation...\n";
    generatePDBsAndMoveTables(); // This now calls the correct, robust function
    std::cout << "Phase 2 generation complete.\n";
    initialized = true;
}

int Phase2Heuristic::calculate(int c_perm, int e_perm)
{
    if (!initialized)
    {
        initialize();
    }
    
    // Special case: if e_perm is 40319, it means edges 8-11 are not in correct positions
    // Return a high heuristic value to indicate this state is far from solved
    if (e_perm == 40319) {
        return 10; // High value to indicate many moves needed
    }
    
    return std::max(corner_permutation_pdb[c_perm], edge_permutation_pdb[e_perm]);
}