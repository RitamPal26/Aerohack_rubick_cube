// Phase1Heuristic.h
#pragma once

#include "Cube.h"
#include <vector>

class Phase1Heuristic
{
public:
    static void initialize();
    static int calculate(const Cube &cube);

private:
    static bool initialized;
    // PDBs store the number of moves to solve the pattern.
    static std::vector<int> corner_orientation_pdb;
    static std::vector<int> edge_orientation_pdb;

    // Functions to generate the databases via BFS.
    static void generateCornerPDB();
    static void generateEdgePDB();
};