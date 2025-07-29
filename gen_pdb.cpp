#include "PatternDatabase.h"

int main() {
  // must match the filename your solver will use later
  const std::string fn = "corner_pdb.dat";  
  PatternDatabase pdb(fn);   // ctor will load if exists, otherwise call generate() & save
  return 0;
}