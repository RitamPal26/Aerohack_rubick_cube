// Phase2Heuristic.h
#pragma once

#include "Cube.h"
#include <vector>

class Phase2Heuristic
{
public:
    static void initialize();
     static int calculate(int c_perm, int e_perm);
    static void generateMoveTables();

    static std::vector<std::vector<int>> corner_move_table;
    static std::vector<std::vector<int>> edge_move_table;
    static void generatePDBsAndMoveTables();

private:
    static bool initialized;
    static std::vector<int> corner_permutation_pdb;
    static std::vector<int> edge_permutation_pdb;

    static void generateCornerPDB();
    static void generateEdgePDB();

    static void generatePermutationPDBs();
};