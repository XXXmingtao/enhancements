#ifndef TILE_BAG_H
#define TILE_BAG_H 

#include "Type.h"

class Node {
public:
   Node(Tile tile, Node* next);

   Tile tile;
   Node* next;
};

class TileBag {
public:
   TileBag();
   TileBag(TileBag& other);
   ~TileBag();

   /**
    * Return the current size of the Tile Bag.
    */
   int size();

   /**
    * Get the tile at the given index.
    */
   Tile get(int index);

   /**
    * Add the tile to the back of the Tile Bag
    */
   void addBack(Tile tile);

   /**
    * Add the tile to the front of the Tile Bag
    */
   void addFront(Tile tile);

   /**
    * Remove the tile at the back of the Tile Bag
    */
   void removeBack();

   /**
    * Remove the tile at the front of the Tile Bag
    */
   void removeFront();

   /**
    * Removes all tiles from the Tile Bag
    */
   void clear();

private:

   Node* head;
};

#endif // TILE_BAG_H
