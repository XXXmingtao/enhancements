#include "Pattern.h"
#include "iostream"

Pattern::Pattern(){
    pattern = new std::vector<Tile>[ROW];
    for(int i = 0; i != ROW; ++i) {
        for(int j = 0; j != i+1; ++j) {
            pattern[i].push_back(NO_TILE);
        }
    }
}

Pattern::~Pattern(){
    delete pattern;
}

std::vector<Tile> Pattern::getPatternLine(int index){
    return pattern[index];
}

bool Pattern::placeTile(Tile tile, unsigned int row){
    bool excute = false;
    unsigned int index = 0;
    for(Tile tile:pattern[row-1]){
        if(tile!=NO_TILE){
            ++index;
        }
    }
    if(index != row){
        pattern[row-1][row-index-1] = tile;
        excute = true;
    }
    return excute; 
}
Tile Pattern::getFirstTile(int row){
    return pattern[row-1][0];
}

Tile Pattern::getLastTile(int row){
    return pattern[row-1][row-1];
}

void Pattern::clear(int index){
    for(unsigned int i = 0; i < pattern[index].size();i++) {
        pattern[index][i] = NO_TILE;
    }
}