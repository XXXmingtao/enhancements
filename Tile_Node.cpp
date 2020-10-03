#include "Tile_Node.h"

Tile_Node::Tile_Node(Tile tile) {
    this->tile = tile;
    this->left = nullptr;
    this->right = nullptr;
}

Tile_Node::Tile_Node(const Tile_Node& other) {
    this->tile = tile;
    this->left = nullptr;
    this->right = nullptr;
}

Tile_Node::~Tile_Node() {
    left = nullptr;
    right = nullptr;
}