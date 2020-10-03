#ifndef TILE_H
#define TILE_H

#include "Type.h"
#include <memory>

class Tile_Node {
public:
    Tile_Node(Tile tile);
    Tile_Node(const Tile_Node& other);
    ~Tile_Node();

    //data of the root node
    Tile tile;

    //left & right node
    std::shared_ptr<Tile_Node> left;
    std::shared_ptr<Tile_Node> right;
};

#endif // TILE_H
