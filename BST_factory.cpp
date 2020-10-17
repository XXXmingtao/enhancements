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

bool BST_factory::isEmpty() {
    bool isEmpty;
    if(root == nullptr) {
        isEmpty = true;
    } else {
        isEmpty = false;
    }
    return isEmpty;
}

int BST_factory::size(std::shared_ptr<Tile_Node> node) {
    int count;
    if(node == nullptr) {
        count = 0;
    } else {
        count = size(node->left) + 1 + size(node->right);
    }
    return count;
}

std::shared_ptr<Tile_Node> BST_factory::getRoot() {
    return root;
}

bool BST_factory::contains(const Tile tile) const {
    
    return contains(root, tile);
}

bool BST_factory::contains(std::shared_ptr<Tile_Node> node, const Tile tile) const {
        
    bool Isfound = false;

    if(node == nullptr) {
        Isfound = false;
    }
    else if(tile == node->tile) {
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
    std::cout << std::endl;
}

void BST_factory::dfs(std::shared_ptr<Tile_Node> node) const {
    
    if(node != nullptr) {

    dfs(node->left);

    std::cout << convertToChar(node->tile) << " ";

    dfs(node->right);

    }
}

void BST_factory::addRestTileToCenter(BST_factory* center) {
    addRestTileToCenter(root, center);
}

void BST_factory::addRestTileToCenter(std::shared_ptr<Tile_Node> node, BST_factory* center) {
    if(node != nullptr) {

        addRestTileToCenter(node->left, center);

        center->add(node->tile);

        addRestTileToCenter(node->right, center);
    }
}

std::shared_ptr<Tile_Node> BST_factory::findTile(const Tile tile) {
    return findTile(root, tile);
}

std::shared_ptr<Tile_Node> BST_factory::findTile(std::shared_ptr<Tile_Node> node, const Tile tile) {
    std::shared_ptr<Tile_Node> returnNode;

    if(node != nullptr) {
        if(node->tile == tile) {
            returnNode = node;
        }
        else {
            if(tile < node->tile) {
                returnNode = findTile(node->left, tile);
            } else {
                returnNode = findTile(node->right, tile);
            }

        }
    }
    return returnNode;
}

std::shared_ptr<Tile_Node> minValueNode(std::shared_ptr<Tile_Node> node) {
    std::shared_ptr<Tile_Node> returnNode;
    if(node->left != nullptr) {
        returnNode = node;
    }
    else {
        returnNode = minValueNode(node->left);
    }
    return returnNode;
}

int BST_factory::remove(const Tile tile) {
    int count = 0;
    while(contains(tile)) {
        root = remove(root, tile);
        count++;
    }
    
    return count;
}

std::shared_ptr<Tile_Node> BST_factory::remove(std::shared_ptr<Tile_Node> node, const Tile tile) {

    if(!node) {
        node = nullptr;
    }
        if(node->tile > tile) {
            node->left = remove(node->left, tile);
        } 
        else if(node->tile < tile){
            node->right = remove(node->right, tile);
        } else {
            if(!node->left || !node->right) {
                if(node->left) {
                    node = node->left;
                } else {
                    node = node->right;
                }   
            } else {
                std::shared_ptr<Tile_Node> current = node->right;   
                while(current->left) {
                    current = current->left;
                }
                node->tile = current->tile;
                node->right = remove(node->right, current->tile);
            }
        }
    return node;
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