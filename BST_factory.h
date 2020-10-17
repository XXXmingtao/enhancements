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

    //Take rest tiles to center factory
    void addRestTileToCenter(BST_factory* center);
    void addRestTileToCenter(std::shared_ptr<Tile_Node> node, BST_factory* center);

    //Find certain tiles in BST
    std::shared_ptr<Tile_Node> findTile(const Tile tile);
    std::shared_ptr<Tile_Node> findTile(std::shared_ptr<Tile_Node> node, const Tile tile);

    //Remove tile from BST
    int remove(const Tile tile);
    std::shared_ptr<Tile_Node> remove(std::shared_ptr<Tile_Node> node, const Tile tile);

    //Find the Minimal value
    std::shared_ptr<Tile_Node> minValueNode(std::shared_ptr<Tile_Node> node);

    //Check if BST is empty
    bool isEmpty();

    //Size of the tree
    int size(std::shared_ptr<Tile_Node> node);
    std::shared_ptr<Tile_Node> getRoot();

    char convertToChar(Tile tile) const;

private:
    std::shared_ptr<Tile_Node> root;
};

#endif // BST_FACTORY_H