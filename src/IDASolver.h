#ifndef IDA_SOLVER_H
#define IDA_SOLVER_H
#include "PatternDatabase.h"

#include <string>
#include <vector>

class Cube; // Forward declaration

class IDASolver
{
public:
    std::string solve(Cube start_state);
    PatternDatabase corner_pdb;
    IDASolver();

private:
    // Declare the two new search functions for each phase
    bool search_phase1(Cube &cube, int g, int threshold, std::vector<std::string> &path);
    bool search_phase2(int c_perm, int e_perm, int g, int threshold, std::vector<std::string> &path);
    
};

#endif // IDA_SOLVER_H