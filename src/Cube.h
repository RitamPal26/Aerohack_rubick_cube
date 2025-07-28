#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <vector>
#include <array>

class Cube
{
public:
    // --- Slot-Centric Data Model ---
    // cp[i] = piece that is currently in corner slot i
    std::array<int, 8> cp;
    // co[i] = orientation of the piece in corner slot i
    std::array<int, 8> co;
    // ep[i] = piece that is currently in edge slot i
    std::array<int, 12> ep;
    // eo[i] = orientation of the piece in edge slot i
    std::array<int, 12> eo;


    // --- Core Functions ---
    Cube(); // Constructor to initialize to solved state
    void applyMoves(const std::string &move_sequence);
    bool isSolved() const;
    void print() const; // Needs to be adapted from your original
    void scramble();

    // --- Coordinate (Indexing) Functions ---
    int getCornerOrientationIndex() const;
    int getEdgeOrientationIndex() const;
    int getCornerPermutationIndex() const;
    int getEdgePermutationIndex() const; // U/D Slice Permutation for Phase 2
    bool isInG1() const; // Check if cube is in G1 state (all orientations 0)

private:
    // Internal function to apply a single move using permutation multiplication
    void multiply(const Cube &move_cube);
    void cornerMultiply(const Cube &move_cube);
    void edgeMultiply(const Cube &move_cube);
};

#endif // CUBE_H