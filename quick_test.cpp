#include <iostream>
#include "Cube.h"

void test_single_move(const std::string &move) {
    Cube cube;
    std::cout << "Testing " << move << ": ";
    cube.applyMoves(move);
    cube.applyMoves(move + "'");
    std::cout << (cube.isSolved() ? "PASS" : "FAIL") << std::endl;
}

int main() {
    std::cout << "=== Move Tests ===" << std::endl;
    test_single_move("R");
    test_single_move("L"); 
    test_single_move("U");
    test_single_move("D");
    test_single_move("F");
    test_single_move("B");
    return 0;
}
