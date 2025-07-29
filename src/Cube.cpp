#include "Cube.h"
#include <iostream>
#include <numeric>   // Required for std::iota
#include <algorithm> // Required for std::find
#include <random>

const char *colors_map[] = {"W", "Y", "G", "B", "O", "R"};

// Defines the colors of each of the 8 corner PIECES' stickers in (U/D, L/R, F/B) order
const int corner_colors[8][3] = {
    {0, 5, 2}, {0, 2, 4}, {0, 4, 3}, {0, 3, 5}, // URF, UFL, ULB, UBR
    {1, 2, 5},
    {1, 4, 2},
    {1, 3, 4},
    {1, 5, 3} // DFR, DLF, DBL, DRB
};

// Defines the colors of each of the 12 edge PIECES' stickers
const int edge_colors[12][2] = {
    {0, 5}, {0, 2}, {0, 4}, {0, 3}, // UR, UF, UL, UB
    {1, 5},
    {1, 2},
    {1, 4},
    {1, 3}, // DR, DF, DL, DB
    {2, 5},
    {2, 4},
    {3, 4},
    {3, 5} // FR, FL, BL, BR
};

// Maps the 8 corner SLOTS to their 3 facelet positions on a standard U-R-F-D-L-B unfolded cube
const int corner_facelets[8][3] = {
    {8, 47, 18}, {6, 19, 38}, {0, 36, 29}, {2, 27, 46}, {11, 24, 48}, {9, 41, 25}, {15, 33, 42}, {17, 51, 34}};

// Maps the 12 edge SLOTS to their 2 facelet positions  
const int edge_facelets[12][2] = {
    {5, 10}, {7, 19}, {3, 37}, {1, 46}, {28, 16}, {30, 25}, {34, 43}, {32, 52}, {12, 21}, {39, 23}, {50, 41}, {48, 14}};
// Helper for permutation indexing
long long factorial(int n)
{
    if (n < 0)
        return 0;
    long long res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

// ========== The 6 Basic Moves (Defined as Cube Objects) ==========
// These static objects represent a single clockwise turn.

const Cube &getMoveU()
{
    static Cube move;
    static bool init = false;
    if (!init)
    {
        move.cp = {3, 0, 1, 2, 4, 5, 6, 7};               // Permutation of corner slots for U
        move.co = {0, 0, 0, 0, 0, 0, 0, 0};               // No corner orientation change for U
        move.ep = {3, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11}; // Permutation of edge slots for U
        move.eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // No edge orientation change for U
        init = true;
    }
    return move;
}

const Cube &getMoveR()
{
    static Cube move;
    static bool init = false;
    if (!init)
    {
        move.cp = {4, 1, 2, 0, 7, 5, 6, 3};
        move.co = {2, 0, 0, 1, 1, 0, 0, 2};
        move.ep = {11, 1, 2, 3, 8, 5, 6, 7, 0, 9, 10, 4};  // Fixed: R move edge cycle 0→8→4→11→0
        move.eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // No edge orientation change for R
        init = true;
    }
    return move;
}

const Cube &getMoveF()
{
    static Cube move;
    static bool init = false;
    if (!init)
    {
        move.cp = {1, 5, 2, 3, 0, 4, 6, 7};
        move.co = {1, 2, 0, 0, 2, 1, 0, 0};
        move.ep = {0, 9, 2, 3, 4, 8, 6, 7, 5, 1, 10, 11};  // Fixed: F move edge cycle 1→8→5→9→1
        move.eo = {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};
        init = true;
    }
    return move;
}

const Cube &getMoveD()
{
    static Cube move;
    static bool init = false;
    if (!init)
    {
        move.cp = {0, 1, 2, 3, 5, 6, 7, 4};
        move.co = {0, 0, 0, 0, 0, 0, 0, 0};               // No corner orientation change for D
        move.ep = {0, 1, 2, 3, 5, 6, 7, 4, 8, 9, 10, 11};
        move.eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // No edge orientation change for D
        init = true;
    }
    return move;
}

const Cube &getMoveL()
{
    static Cube move;
    static bool init = false;
    if (!init)
    {
        move.cp = {0, 2, 6, 3, 4, 1, 5, 7};
        move.co = {0, 1, 2, 0, 0, 2, 1, 0};
        move.ep = {0, 1, 9, 3, 4, 5, 10, 7, 8, 6, 2, 11};  // Fixed: L move edge cycle 2→10→6→9→2
        move.eo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // No edge orientation change for L
        init = true;
    }
    return move;
}

const Cube &getMoveB()
{
    static Cube move;
    static bool init = false;
    if (!init)
    {
        move.cp = {0, 1, 3, 7, 4, 5, 2, 6};
        move.co = {0, 0, 1, 2, 0, 0, 2, 1};
        move.ep = {0, 1, 2, 11, 4, 5, 6, 10, 8, 9, 3, 7};  // Fixed: B move edge cycle 3→10→7→11→3
        move.eo = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1};
        init = true;
    }
    return move;
}

// ========== Constructor and Core Logic ==========

// Initialize a solved cube
Cube::Cube()
{
    std::iota(cp.begin(), cp.end(), 0);
    std::iota(ep.begin(), ep.end(), 0);
    co.fill(0);
    eo.fill(0);
}

// Multiply this cube's state by a move cube's state
void Cube::multiply(const Cube &move_cube)
{
    cornerMultiply(move_cube);
    edgeMultiply(move_cube);
}

void Cube::cornerMultiply(const Cube &move_cube)
{
    std::array<int, 8> new_cp;
    std::array<int, 8> new_co;

    for (int i = 0; i < 8; ++i)
    {
        // New piece in slot 'i' is the piece that was in slot 'move_cube.cp[i]'
        new_cp[i] = this->cp[move_cube.cp[i]];
        // New orientation is the sum of the original orientations
        new_co[i] = (this->co[move_cube.cp[i]] + move_cube.co[i]) % 3;
    }
    this->cp = new_cp;
    this->co = new_co;
}

void Cube::edgeMultiply(const Cube &move_cube)
{
    std::array<int, 12> new_ep;
    std::array<int, 12> new_eo;

    for (int i = 0; i < 12; ++i)
    {
        new_ep[i] = this->ep[move_cube.ep[i]];
        new_eo[i] = (this->eo[move_cube.ep[i]] + move_cube.eo[i]) % 2;
    }
    this->ep = new_ep;
    this->eo = new_eo;
}

// Apply a sequence of moves like "U F' R2"
void Cube::applyMoves(const std::string &move_sequence)
{
    std::string current_move;
    for (size_t i = 0; i < move_sequence.length(); ++i)
    {
        if (move_sequence[i] == ' ')
            continue;

        current_move += move_sequence[i];
        if (i + 1 < move_sequence.length() && (move_sequence[i + 1] == '\'' || move_sequence[i + 1] == '2'))
        {
            current_move += move_sequence[++i];
        }

        const Cube *move_cube_ptr = nullptr;
        switch (current_move[0])
        {
        case 'U':
            move_cube_ptr = &getMoveU();
            break;
        case 'R':
            move_cube_ptr = &getMoveR();
            break;
        case 'F':
            move_cube_ptr = &getMoveF();
            break;
        case 'D':
            move_cube_ptr = &getMoveD();
            break;
        case 'L':
            move_cube_ptr = &getMoveL();
            break;
        case 'B':
            move_cube_ptr = &getMoveB();
            break;
        }

        if (move_cube_ptr)
        {
            int num_turns = 1;
            if (current_move.length() > 1)
            {
                if (current_move[1] == '\'')
                    num_turns = 3;
                else if (current_move[1] == '2')
                    num_turns = 2;
            }
            for (int j = 0; j < num_turns; ++j)
            {
                this->multiply(*move_cube_ptr);
            }
        }
        current_move.clear();
    }
}

// ========== Indexing (Coordinate) Functions ==========

// Phase 1: Corner Orientation (Twist)
int Cube::getCornerOrientationIndex() const
{
    int index = 0;
    for (int i = 0; i < 7; ++i)
    { // Last corner is dependent
        index = 3 * index + this->co[i];
    }
    return index;
}

// Phase 1: Edge Orientation (Flip)
int Cube::getEdgeOrientationIndex() const
{
    int index = 0;
    for (int i = 0; i < 11; ++i)
    { // Last edge is dependent
        index = 2 * index + this->eo[i];
    }
    return index;
}

// Phase 2: Corner Permutation
int Cube::getCornerPermutationIndex() const
{
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        int permutations = 0;
        for (int j = i + 1; j < 8; j++)
        {
            if (cp[i] > cp[j])
            {
                permutations++;
            }
        }
        index += permutations * factorial(7 - i);
    }
    return index;
}

// Phase 2: U/D Slice Edge Permutation (Permutation of pieces 0-7 within slots 0-7)
int Cube::getEdgePermutationIndex() const
{
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        int permutations = 0;
        for (int j = i + 1; j < 8; j++)
        {
            if (ep[i] > ep[j])
            {
                permutations++;
            }
        }
        index += permutations * factorial(7 - i);
    }
    return index;
}

// ========== Utility Functions ==========

bool Cube::isSolved() const
{
    for (int i = 0; i < 8; ++i)
        if (cp[i] != i || co[i] != 0)
            return false;
    for (int i = 0; i < 12; ++i)
        if (ep[i] != i || eo[i] != 0)
            return false;
    return true;
}

void Cube::scramble()
{
    const char *moves[] = {"U", "D", "L", "R", "F", "B"};
    const char *mods[] = {"", "'", "2"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> move_dist(0, 5);
    std::uniform_int_distribution<> mod_dist(0, 2);

    std::string scramble_str;
    for (int i = 0; i < 25; ++i)
    {
        scramble_str += moves[move_dist(gen)];
        scramble_str += mods[mod_dist(gen)];
        scramble_str += " ";
    }
    applyMoves(scramble_str);
}

void Cube::print() const
{
    std::array<int, 54> facelets;

    // Place centers
    facelets[4] = 0;
    facelets[13] = 5;
    facelets[22] = 2; // U, R, F
    facelets[31] = 1;
    facelets[40] = 4;
    facelets[49] = 3; // D, L, B

    // Place corner colors
    for (int i = 0; i < 8; ++i)
    { // For each corner SLOT i
        int piece = cp[i];
        int orientation = co[i];
        for (int j = 0; j < 3; ++j)
        {
            int facelet_pos = corner_facelets[i][j];
            facelets[facelet_pos] = corner_colors[piece][(j + orientation) % 3];
        }
    }

    // Place edge colors
    for (int i = 0; i < 12; ++i)
    { // For each edge SLOT i
        int piece = ep[i];
        int orientation = eo[i];
        for (int j = 0; j < 2; ++j)
        {
            int facelet_pos = edge_facelets[i][j];
            facelets[facelet_pos] = edge_colors[piece][(j + orientation) % 2];
        }
    }

    // Print the reconstructed state in a standard URFDLB layout
    const char *faces_map[] = {"Up", "Right", "Front", "Down", "Left", "Back"};
    const int face_start_indices[] = {0, 9, 18, 27, 36, 45};

    for (int i = 0; i < 6; ++i)
    {
        std::cout << faces_map[i] << ":\n";
        for (int row = 0; row < 3; ++row)
        {
            std::cout << "  ";
            for (int col = 0; col < 3; ++col)
            {
                std::cout << colors_map[facelets[face_start_indices[i] + row * 3 + col]] << " ";
            }
            std::cout << "\n";
        }
    }

    if (isSolved())
    {
        std::cout << "\nCube state is SOLVED.\n";
    }
    else
    {
        std::cout << "\nCube state is NOT SOLVED.\n";
    }
}

bool Cube::isInG1() const
{
    for (int orientation : co)
    {
        if (orientation != 0)
            return false;
    }
    for (int orientation : eo)
    {
        if (orientation != 0)
            return false;
    }
    return true;
}

// Convert internal representation to 54-sticker state array
std::array<int, 54> Cube::getState() const
{
    std::array<int, 54> state;
    
    // Initialize with solved state colors
    // Face order: U(0-8), R(9-17), F(18-26), D(27-35), L(36-44), B(45-53)
    for (int i = 0; i < 9; i++) state[i] = WHITE;       // U face
    for (int i = 9; i < 18; i++) state[i] = RED;        // R face  
    for (int i = 18; i < 27; i++) state[i] = GREEN;     // F face
    for (int i = 27; i < 36; i++) state[i] = YELLOW;    // D face
    for (int i = 36; i < 45; i++) state[i] = ORANGE;    // L face
    for (int i = 45; i < 54; i++) state[i] = BLUE;      // B face
    
    // Apply corner permutations and orientations
    for (int i = 0; i < 8; i++) {
        int piece = cp[i];
        int orientation = co[i];
        
        // Apply corner colors based on piece and orientation
        for (int j = 0; j < 3; j++) {
            int sticker_pos = corner_facelets[i][j];
            int color_index = (j + orientation) % 3;
            state[sticker_pos] = corner_colors[piece][color_index];
        }
    }
    
    // Apply edge permutations and orientations  
    for (int i = 0; i < 12; i++) {
        int piece = ep[i];
        int orientation = eo[i];
        
        // Apply edge colors based on piece and orientation
        for (int j = 0; j < 2; j++) {
            int sticker_pos = edge_facelets[i][j];
            int color_index = (j + orientation) % 2;
            state[sticker_pos] = edge_colors[piece][color_index];
        }
    }
    
    return state;
}