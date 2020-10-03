#include "Wall.h"

Wall::Wall(){
    wall = new Tile*[ROW];
    for(int i = 0; i != ROW; i++) {
        wall[i] = new Tile[COLUMN];
        for(int j = 0; j != COLUMN; j++) {
            wall[i][j] = NO_TILE;
        }
    }
}

Wall::~Wall(){
    for(int i = 0; i != ROW; i++) {
        delete wall[i];
    }
    delete wall;
}

int Wall::tile(Tile tile, int row){
    int score = 0;
    int col = (tile + row) % COLUMN;
    wall[col][row] = tile;
    bool x_adjacent = false;
    bool y_adjacent = false;
    bool continues = true;
    
    score++;
    // Down-check
    for(int i = row+1; i < ROW && continues; i++) {
        if(wall[col][i] != NO_TILE) {
            score++;
            y_adjacent = true;
        }
        else {
            continues = false;
        }
    }
    
    continues = true;
    // Up-check
    for(int i = row-1; i >= 0 && continues; i--) {
        if(wall[col][i] != NO_TILE) {
            score++;
            y_adjacent = true;
        }
        else {
            continues = false;
        }
    }

    continues = true;
    // Right-check
    for(int i = col+1; i < ROW && continues; i++) {
        if(wall[i][row] != NO_TILE) {
            score++;
            x_adjacent = true;
        }
        else {
            continues = false;
        }
    }

    continues = true;
    // Left-check
    for(int i = col-1; i >= 0 && continues; i--) {
        if(wall[i][row] != NO_TILE) {
            score++;
            x_adjacent = true;
        }
        else {
            continues = false;
        }
    }

    if(x_adjacent && y_adjacent) {
        score++;
    }
    
    return score;
}

bool Wall::checkColor(Tile tile, int row){
    bool hasSameColor = false;
    for(int i=0;i!=COLUMN;++i){
        if(wall[i][row-1]==tile){
            hasSameColor = true;
        }
    }
    return hasSameColor;
}

Tile** Wall::getWall(){
    return wall;
}