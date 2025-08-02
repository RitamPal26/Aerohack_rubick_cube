# Algorithm Implementation Details

## Coordinate Systems

### Phase 1 Coordinates
- **Corner Orientation**: Maps to 0-2186 (3^7 states)
- **Edge Orientation**: Maps to 0-2047 (2^11 states)

### Phase 2 Coordinates  
- **Corner Permutation**: Maps to 0-40319 (8! states)
- **Edge Permutation**: Maps to 0-40319 (8! states in G1)

## Pattern Database Generation

Pattern databases are generated using breadth-first search:
1. Start from solved state (index 0)
2. Apply all possible moves
3. Record minimum distance to reach each coordinate
4. Continue until maximum depth (typically 11-12 moves)

## Move Representation

Moves are represented as permutations of corner and edge arrays:
- Corner permutation (cp): which piece is in each corner slot
- Corner orientation (co): how each corner piece is oriented
- Edge permutation (ep): which piece is in each edge slot  
- Edge orientation (eo): how each edge piece is oriented

## G1 Subgroup Definition

A cube state is in G1 if and only if:
1. All corner orientations are 0 (co[i] == 0 for all i)
2. All edge orientations are 0 (eo[i] == 0 for all i)  
3. Middle-slice edges (FR,FL,BL,BR) are in positions 8,9,10,11

This reduces the search space from ~43 quintillion to ~19 billion states.
