#include "Factory.h"

Factory::Factory(){
    factory = new std::vector<Tile>;
}

Factory::~Factory() {
    delete factory;
}

void Factory::addTile(Tile tile) {
    factory->push_back(tile);
}

Tile Factory::getTile(unsigned int i) {
    return factory->at(i);
}

std::vector<Tile>* Factory::getAllTiles() {
    return factory;
}

bool Factory::find(Tile tile) {
    bool found = false;
    for(Tile tileInFactory:*factory) {
        if(tileInFactory==tile) {
            found = true;
        }
    }
    return found;
}

unsigned int Factory::size() {
    return factory->size();
}

bool Factory::isEmpty() {
    return factory->empty();
}

void Factory::clearFactory() {
    factory->clear();
}

