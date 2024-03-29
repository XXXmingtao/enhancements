#ifndef PATTERN
#define PATTERN

#include "Type.h"

#include <vector>

class Pattern{
public:
    Pattern();
    ~Pattern();

    // Get a pattern line
    std::vector<Tile> getPatternLine(int index);
    // Put a type of tiles on the pattern line of the specified number of rows
    bool placeTile(Tile tiles, unsigned int row);
    // Return the tile at the head of a pattern line
    Tile getFirstTile(int row);
    // Return the tile at the back of a pattern line
    Tile getLastTile(int row);
    // Clear a pattern line
    void clear(int index);

private:
    std::vector<Tile>* pattern;
};

#endif // PATTERN