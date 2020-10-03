#include "BST_factory.h"
#include <iostream>

BST_factory::BST_factory() {
    root = nullptr;
}

BST_factory::~BST_factory() {

    clear();
}

void BST_factory::clear() {
    root = nullptr;
}

bool BST_factory::contains(const Tile tile) const {

    return contains(root, tile);

}

bool BST_factory::contains(std::shared_ptr<Tile_Node> node, const Tile tile) const {
        
    bool Isfound;

    if(node == nullptr) {
        Isfound = false;
    }
    if(tile == node->tile) {
        Isfound = true;
    } else {
        if(tile < node->tile) {
            Isfound = contains(node->left, tile);
        } else {
            Isfound = contains(node->right, tile);
        }
    }

    return Isfound;
}

void BST_factory::add(const Tile tile) {
    root = add(root, tile);
}

std::shared_ptr<Tile_Node> BST_factory::add(std::shared_ptr<Tile_Node> node, const Tile tile) {
    
    std::shared_ptr<Tile_Node> returnNode;

    if(node == nullptr) {
        returnNode = std::make_shared<Tile_Node>(tile);
    } else {
        if(tile < node->tile) {
            std::shared_ptr<Tile_Node> subtree = add(node->left, tile);
            node->left = subtree;
            returnNode = node;
        } else {
            std::shared_ptr<Tile_Node> subtree = add(node->right, tile);
            node->right = subtree;
            returnNode = node;
        }
    }

    return returnNode;

}

void BST_factory::dfs() const{
    dfs(root);
}

void BST_factory::dfs(std::shared_ptr<Tile_Node> node) const {
    
    if(node != nullptr) {

    dfs(node->left);

    std::cout << convertToChar(node->tile) << " ";

    dfs(node->right);

    }
}

std::shared_ptr<Tile_Node> BST_factory::find(const Tile tile) {
    return find(root, tile);
}

std::shared_ptr<Tile_Node> BST_factory::find(std::shared_ptr<Tile_Node> node, const Tile tile) {
    std::shared_ptr<Tile_Node> returnNode;

    if(node != nullptr) {

        if(tile < node->tile) {
            returnNode = find(node->left, tile);
        } else {
            returnNode = find(node->right, tile);
        }

    }

    return returnNode;
}

char BST_factory::convertToChar(Tile tile) const{
    char charTile = N;
    if(tile == RED){
        charTile = R;
    } else if(tile == YELLOW){
        charTile = Y;
    } else if(tile == DARK_BLUE){
        charTile = B;
    } else if(tile == LIGHT_BLUE){
        charTile = L;
    } else if(tile == BLACK){
        charTile = U;
    } else if(tile == FIRST_PLAYER){
        charTile = F;
    }
    return charTile;
}