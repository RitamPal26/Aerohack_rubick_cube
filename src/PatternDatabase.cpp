#include "PatternDatabase.h"
#include "Cube.h"
#include <fstream>
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// --- Corner Definitions ---
const int corner_sticker_map[8][3] = {
    {8, 47, 18}, {6, 19, 38}, {0, 36, 29}, {2, 27, 46}, {11, 24, 48}, {9, 41, 25}, {15, 33, 42}, {17, 51, 34}};
const int corner_piece_def[8][3] = {
    {WHITE, RED, GREEN}, {WHITE, GREEN, ORANGE}, {WHITE, ORANGE, BLUE}, {WHITE, BLUE, RED}, {YELLOW, GREEN, RED}, {YELLOW, ORANGE, GREEN}, {YELLOW, BLUE, ORANGE}, {YELLOW, RED, BLUE}};

const int CORNER_PERM_SIZE = 40320;
const int CORNER_ORIENT_SIZE = 2187;
const int PDB_SIZE = CORNER_PERM_SIZE * CORNER_ORIENT_SIZE;

static long long factorial(int n)
{
    return (n < 2) ? 1 : n * factorial(n - 1);
}

// --- Constructor and PDB Generation ---
PatternDatabase::PatternDatabase(const std::string &filename) : pdb_filename(filename)
{
    std::ifstream pdb_file(pdb_filename, std::ios::binary);
    if (pdb_file)
    {
        std::cout << "Loading Pattern Database from " << filename << "..." << std::endl;
        database.resize(PDB_SIZE);
        pdb_file.read(reinterpret_cast<char *>(database.data()), PDB_SIZE * sizeof(int));
    }
    else
    {
        std::cout << "Pattern Database file not found. Generating..." << std::endl;
        generate();
    }
}

void PatternDatabase::generate()
{
    database.assign(PDB_SIZE, -1);
    std::queue<std::pair<Cube, int>> q;
    Cube solved_cube;

    long long solved_index = getHeuristic(solved_cube, true);
    database[solved_index] = 0;
    q.push({solved_cube, 0});
    int max_depth = 0;

    const std::vector<std::string> all_moves = {"U", "U'", "D", "D'", "F", "F'", "B", "B'", "L", "L'", "R", "R'"};

    while (!q.empty())
    {
        Cube current_cube = q.front().first;
        int current_depth = q.front().second;
        q.pop();

        if (current_depth > max_depth)
        {
            max_depth = current_depth;
            std::cout << "Reached PDB depth: " << max_depth << std::endl;
        }

        if (current_depth >= 11)
            continue; // Optimization: max depth for corners is 11

        for (const auto &move : all_moves)
        {
            Cube next_cube = current_cube;
            next_cube.applyMoves(move);
            long long next_index = getHeuristic(next_cube, true);
            if (database.at(next_index) == -1)
            {
                database[next_index] = current_depth + 1;
                q.push({next_cube, current_depth + 1});
            }
        }
    }

    std::cout << "PDB Generation Complete. Saving to " << pdb_filename << "..." << std::endl;
    std::ofstream pdb_file(pdb_filename, std::ios::binary);
    pdb_file.write(reinterpret_cast<const char *>(database.data()), PDB_SIZE * sizeof(int));
}

// --- Main Heuristic Calculation ---
int PatternDatabase::getHeuristic(const Cube &cube) const
{
    return getHeuristic(cube, false);
}

// Private helper for generation vs. lookup
int PatternDatabase::getHeuristic(const Cube &cube, bool is_generating) const
{
    const std::array<int, 54> &st = cube.getState();

    // --- Piece Identification and Orientation ---
    int p[8];
    int o[8];
    std::vector<int> p_sorted(3);

    for (int i = 0; i < 8; ++i)
    { // For each location
        p_sorted[0] = st[corner_sticker_map[i][0]];
        p_sorted[1] = st[corner_sticker_map[i][1]];
        p_sorted[2] = st[corner_sticker_map[i][2]];
        std::sort(p_sorted.begin(), p_sorted.end());

        for (int j = 0; j < 8; ++j)
        { // Find which piece it is
            std::vector<int> piece_colors = {corner_piece_def[j][0], corner_piece_def[j][1], corner_piece_def[j][2]};
            std::sort(piece_colors.begin(), piece_colors.end());
            
            if (p_sorted[0] == piece_colors[0] && p_sorted[1] == piece_colors[1] && p_sorted[2] == piece_colors[2])
            {
                p[i] = j; // Piece j is at location i
                break;
            }
        }

        // Orientation
        if (st[corner_sticker_map[i][0]] == WHITE || st[corner_sticker_map[i][0]] == YELLOW)
            o[i] = 0;
        else if (st[corner_sticker_map[i][1]] == WHITE || st[corner_sticker_map[i][1]] == YELLOW)
            o[i] = 1;
        else
            o[i] = 2;
    }

    // --- Index Calculation ---
    long long perm_idx = 0;
    for (int i = 0; i < 8; i++)
    {
        int rank = 0;
        for (int j = i + 1; j < 8; j++)
            if (p[i] > p[j])
                rank++;
        perm_idx += rank * factorial(7 - i);
    }

    int orient_idx = 0;
    for (int i = 0; i < 7; i++)
        orient_idx = orient_idx * 3 + o[i];

    long long index = perm_idx * CORNER_ORIENT_SIZE + orient_idx;

    if (is_generating)
        return index;

    int distance = database.at(index);
    return (distance == -1) ? 14 : distance;
}