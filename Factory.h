#ifndef FACTORY
#define FACTORY

#include "Type.h"
#include <vector>

class Factory {
public:
    Factory();
    ~Factory();

    //Add tile into factory
    void addTile(Tile tile);

    //Get all tiles in factory
    std::vector<Tile>* getAllTiles();

    //Check if the facory is empty
    bool isEmpty();

    //Size of the factory
    unsigned int size();

    //Get tile within factory
    Tile getTile(unsigned int i);

    //Remove tiles in factory
    void clearFactory();

    //Find
    bool find(Tile tile);

private:
    std::vector<Tile>* factory;
};

#endif //FACTORY