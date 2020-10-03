#ifndef WALL
#define WALL

#include "Type.h"

class Wall{
public:
    Wall();
    ~Wall();

    // Put tiles to the wall and count score
    int tile(Tile tile, int row);
    // Get the tile type in the wall line
    bool checkColor(Tile tile, int row);
    // Return the wall
    Tile** getWall();

private:
    Tile** wall;
};

#endif // WALL