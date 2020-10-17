#ifndef GAME_ENGINE
#define GAME_ENGINE

#include "Player.h"
#include "Type.h"
#include "TileBag.h"
#include "Factory.h"
#include "BST_factory.h"

#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>


class GameEngine{
public:
    GameEngine();
    ~GameEngine();

    // Initialize factories and tile bags
    void initGame(bool testMode, std::string* fileName, unsigned int seed);
    // reset factories
    void resetFactories();
    // Perform the tile-taking stage for each player in turn until no factories have tiles.
    int startTurn(int firstPlayer);
    // End round, perform the wall-tiling phase and score update
    void endRound();
    // Return players
    std::vector<Player*> getPlayers();
    // Determine the winner
    void applyWinLoss();
    // Reset the game
    void resetGame();
    // Print the factories
    void printFactories();
    // Print one player's mosaic
    void printMosaic(Player* player);
    // Check if testing is complete
    bool isTesting();
    // Check if factories are all empty
    bool hasTiles();

private:
    std::vector<Player*> players;
    std::vector<BST_factory*> factories;
    std::vector<Tile> boxLid;
    TileBag* tileBag;
    unsigned int factoryIndex;
    Tile tile;
    unsigned int patternIndex;
    bool process;
    std::vector<std::string>* inputList;
    std::vector<std::string>* loadList;
    unsigned int loadLine;
    bool loadMode;
    bool testMode;
    unsigned int seedNum;

    // Tile-taking stage, take one type of tiles from one factory, the rest of tiles will be sent to the centre factory.
    std::vector<Tile> takeTiles(unsigned int factoryIndex, Tile tile);
    // Execute wall-tiling phase for one player
    void setWall(Player* player);
    // Update score for one player
    void updateScore(Player* player);
    // Recycle all abandon tiles of one player to the back of tile bag
    void recycleTiles(Player* player);
    // Process one player's input
    void processInput(Player* player);
    // Save the game
    void saveGame(std::string name);
    // Convert enum to char
    char convertToChar(Tile tile);
    // Convert input char to the enum
    Tile convertToEnum(char tile);
    // Initialize tile bag
    void initTileBag();
    // Initialize players
    void initPlayers();
    // Check whether the loading is complete
    void checkLoad();
    // Shuffle the tile bag
    template <class T>
    T shuffledTileBag(T tiles, unsigned int seed);
};

#endif // GAME_ENGINE