#ifndef PATTERN_DATABASE_H
#define PATTERN_DATABASE_H

#include <vector>
#include <string>

class Cube; // Forward declaration

class PatternDatabase
{
public:
    PatternDatabase(const std::string &filename);
    int getHeuristic(const Cube &cube) const;

private:
    void generate();

    int getHeuristic(const Cube &cube, bool is_generating) const;

    std::vector<int> database;
    std::string pdb_filename;
};

#endif // PATTERN_DATABASE_H