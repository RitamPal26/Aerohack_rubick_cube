#include <iostream>
#include "Cube.h"
#include "IDASolver.h"



void test_move(const std::string &move_name, const std::string &move_sequence, const std::string &inverse_sequence)
{
    Cube test_cube; // Creates a solved cube

    std::cout << "Testing move: " << move_name << "..." << std::endl;

    // Apply the move
    test_cube.applyMoves(move_sequence);

    // Apply the inverse move
    test_cube.applyMoves(inverse_sequence);

    if (test_cube.isSolved())
    {
        std::cout << "  [✅] SUCCESS: " << move_name << " is reversible." << std::endl;
    }
    else
    {
        std::cout << "  [❌] FAILURE: " << move_name << " is not reversible. Check implementation." << std::endl;
        // Optional: print the cube state to see what went wrong
        // test_cube.print();
    }
}

int main()
{
    std::cout << "Creating a 3x3x3 Rubik's Cube." << std::endl;
    // Correct: Use the default constructor
    Cube my_cube;

    std::string scramble_moves = "F U' R L' D B' U R";
    my_cube.applyMoves(scramble_moves);

    std::cout << "\n--- Scrambled Cube State ---" << std::endl;
    my_cube.print();

    std::cout << "\n--- Starting Solver ---" << std::endl;
    IDASolver solver;
    
    // Debug: Check if cube is already solved before solving
    std::cout << "DEBUG: Cube solved before solving? " << (my_cube.isSolved() ? "YES" : "NO") << std::endl;
    
    std::string solution = solver.solve(my_cube);

    std::cout << "\n--- Solution Found ---" << std::endl;
    std::cout << "Scramble Moves: " << scramble_moves << std::endl;
    std::cout << "Solution Path: " << solution << std::endl;
    std::cout << "Solution length: " << solution.length() << " characters" << std::endl;

    // Debug: Create a copy to test solution on
    Cube test_cube = my_cube;
    std::cout << "\nDEBUG: Applying solution to test cube..." << std::endl;
    test_cube.applyMoves(solution);
    std::cout << "\n--- Final Cube State After Applying Solution ---" << std::endl;
    test_cube.print();

    if (test_cube.isSolved())
    {
        std::cout << "\nVerification successful: The cube is solved!" << std::endl;
    }
    else
    {
        std::cout << "\nVerification failed: The cube is NOT solved." << std::endl;
        std::cout << "DEBUG: This indicates a problem with either:" << std::endl;
        std::cout << "  1. The solver algorithm" << std::endl;
        std::cout << "  2. The move application" << std::endl;
        std::cout << "  3. The solution parsing" << std::endl;
    }

    std::cout << "\n--- Testing Individual Moves ---" << std::endl;
    // Test clockwise moves
    test_move("R", "R", "R'");
    test_move("L", "L", "L'");
    test_move("U", "U", "U'");
    test_move("D", "D", "D'");
    test_move("F", "F", "F'");
    test_move("B", "B", "B'");

    std::cout << "\n";

    // Test counter-clockwise (prime) moves
    test_move("R'", "R'", "R");
    test_move("L'", "L'", "L");
    test_move("U'", "U'", "U");
    test_move("D'", "D'", "D");
    test_move("F'", "F'", "F");
    test_move("B'", "B'", "B");

    return 0;
}