#include "src/Cube.h"
#include "src/Phase2Heuristic.h"
#include <iostream>

int main() {
    std::cout << "=== Phase 2 Move Table Debug ===" << std::endl;
    
    // Initialize Phase 2
    Phase2Heuristic::initialize();
    
    // Test what happens when we have a cube state after Phase 1
    Cube cube;
    cube.applyMoves("F U' R L' D B' U R");
    cube.applyMoves("U F L2 B R F2 U2 B"); // Phase 1 solution
    
    std::cout << "After Phase 1:" << std::endl;
    std::cout << "  Is in G1: " << (cube.isInG1() ? "YES" : "NO") << std::endl;
    std::cout << "  Corner perm: " << cube.getCornerPermutationIndex() << std::endl;
    std::cout << "  Edge perm: " << cube.getEdgePermutationIndex() << std::endl;
    
    int c_perm = cube.getCornerPermutationIndex();
    int e_perm = cube.getEdgePermutationIndex();
    
    std::cout << "  Phase 2 heuristic: " << Phase2Heuristic::calculate(c_perm, e_perm) << std::endl;
    
    // Test a few Phase 2 moves and see what coordinates they produce
    const std::vector<std::string> moves = {"U", "U2", "U'", "D", "D2", "D'", "F2", "B2", "L2", "R2"};
    
    std::cout << "\nTesting Phase 2 moves from this state:" << std::endl;
    for (size_t i = 0; i < moves.size(); i++) {
        Cube test_cube = cube;
        test_cube.applyMoves(moves[i]);
        
        int new_c_perm = test_cube.getCornerPermutationIndex();
        int new_e_perm = test_cube.getEdgePermutationIndex();
        int new_heuristic = Phase2Heuristic::calculate(new_c_perm, new_e_perm);
        
        std::cout << "  " << moves[i] << ": c=" << new_c_perm << ", e=" << new_e_perm << ", h=" << new_heuristic;
        if (new_c_perm == 0 && new_e_perm == 0) {
            std::cout << " [WOULD BE CONSIDERED SOLVED!]";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
