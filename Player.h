#ifndef PLAYER
#define PLAYER

#include "Type.h"
#include "Mosaic.h"

#include <string>

class Player{
public:
    Player(std::string name);
    ~Player();

    // Return name
    std::string getName();
    // Return score
    int getScore();
    // Set name
    void setName(std::string name);
    // Set score
    void setScore(int score);
    // Return this player's mosaic board
    Mosaic* getMosaic();

private:
    std::string name;
    int score;
    Mosaic* mosaic;
};

#endif // PLAYER