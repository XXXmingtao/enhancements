#ifndef BST_FACTORY_H
#define BST_FACTORY_H

#include "Tile_Node.h"
#include <memory>

class BST_factory {
public:

    BST_factory();
    ~BST_factory();

    //clear BST
    void clear();

    //Check if tile contains in BST
    bool contains(const Tile tile) const;
    bool contains(std::shared_ptr<Tile_Node> node, const Tile tile) const;

    //Add tile in BST
    void add(const Tile tile);
    std::shared_ptr<Tile_Node> add(std::shared_ptr<Tile_Node> node, const Tile tile);

    //Display out all tiles in BST in order
    void dfs() const;
    void dfs(std::shared_ptr<Tile_Node> node) const;

    //Find certain tiles in BST
    std::shared_ptr<Tile_Node> find(const Tile tile);
    std::shared_ptr<Tile_Node> find(std::shared_ptr<Tile_Node> node, const Tile tile);

    //Remove tile from BST
    

    char convertToChar(Tile tile) const;

private:
    std::shared_ptr<Tile_Node> root;
};

#endif // BST_FACTORY_H