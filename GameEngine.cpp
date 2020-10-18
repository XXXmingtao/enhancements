#include "GameEngine.h"

GameEngine::GameEngine(){
    tileBag = new TileBag();
    inputList = new std::vector<std::string>;
    loadList = new std::vector<std::string>;
    loadLine = 0;
    seedNum = 0;
}

GameEngine::~GameEngine(){
    // Delete tile bag
    delete tileBag;

    // Delete factories
    for(BST_factory* factory:factories){
        delete factory;
    }
    //delete factories;

    // Delete inputList
    delete inputList;

    // Delete loadList
    delete loadList;
}

void GameEngine::initGame(bool testMode, std::string* fileName, unsigned int seed){
    std::string inputLine;
    seedNum = seed;
    // Setting mode
    this->testMode = testMode;

    // Load file
    if(fileName!=nullptr){
        std::ifstream file(*fileName);
        if(!file) {
            throw std::invalid_argument("Invalid Input - File not exists");
        } else {
            while(std::getline(file,inputLine)){
                    loadList->push_back(inputLine);
            }
            file.close();
        }
        // Check if save file has a valid size
        if(loadList->size()<DEFAULT_PLAYERS+1){
            throw std::invalid_argument("Invalid save data");
        }
    }

    initTileBag();
    initPlayers();

    // Setting loading status
    loadMode = (loadLine!=loadList->size());

    // Initialize factories
    for(int i = 0; i != DEFAULT_FACTORIES; ++i){
        factories.push_back(new BST_factory());
    }
    // Set factories
    resetFactories();
}

void GameEngine::resetFactories(){
    factories[0]->add(FIRST_PLAYER);
     
    for(unsigned int factoryIndex = 1; factoryIndex != factories.size(); ++factoryIndex){
        for(int i = 0; i != TILES_IN_FACTORY; ++i){
            factories[factoryIndex]->add(tileBag->get(0));
            tileBag->removeFront();
        }
    }
}

int GameEngine::startTurn(int firstPlayer){
    int currentPlayer = firstPlayer;
    int returnFirstPlayer = firstPlayer;
    Player* player;

    if(!loadMode&&!testMode){
        std::cout<<"=== Start Round ==="<<std::endl;
    }

    /* If not in test mode, loop till all factories has no tiles;               */
    /* If in test mode, loop till all factories has no tiles or finish loading; */
    while((!testMode&&hasTiles())||(testMode&&hasTiles()&&isTesting())){
        player = players[currentPlayer%players.size()];
        loadMode = (loadLine!=loadList->size());

        // Hide game display when load game
        
        if(!loadMode){
            std::cout<<"TURN FOR PLAYER: "<<player->getName()<<std::endl;
            
            // Print the factories
            printFactories();
            std::cout<<std::endl;   

            // Print the mosaic
            printMosaic(player);
            std::cout<<std::endl;   
        }

        do{
            process = false;
            if(!loadMode){
                std::cout<<"> ";
            }
            
            try{
                // Enter the command
                processInput(player);
                if(process) {
                    // Take tiles from the factory
                    std::vector<Tile> tiles = takeTiles(factoryIndex,tile);
                    
                    // Check first-player marker
                    for(Tile tile:tiles){
                        if(tile==FIRST_PLAYER){
                            returnFirstPlayer = currentPlayer;
                        }
                    }
                    
                    // Put tiles to player's pattern
                    player->getMosaic()->setPattern(tiles,patternIndex);
                }
                
            } catch(std::exception& e){
                process = false;
                if(!loadMode){
                    std::cout<<e.what()<<std::endl;
                }else{
                    std::string error = e.what();
                    throw std::invalid_argument("error in line "+std::to_string(loadLine)+" | "+error);
                }
            }
        } while(!process&&!loadMode);

        if(!loadMode){
            std::cout<<"Turn successful"<<std::endl;
            std::cout<<std::endl; 
        } else {
            checkLoad();
        }

        ++currentPlayer;
    }
    return returnFirstPlayer;
}

void GameEngine::endRound(){
    if(!loadMode&&!testMode){
        std::cout<<"=== END OF ROUND ==="<<std::endl;
        std::cout<<std::endl;   
    }

    for(Player* player:players){
        setWall(player);
        updateScore(player);
        recycleTiles(player);
        player->getMosaic()->newRound();

        if(!loadMode&&!testMode){
            std::cout<<"Score for Player "<<player->getName()<<": "<<player->getScore()<<std::endl;
            std::cout<<std::endl;   
        }
    }
    if(tileBag->size() == 0 && seedNum > 0) {
        std::cout << "Refill tile bag processing..." << std::endl;
        std::vector<Tile> randomizedBoxLid = shuffledTileBag(boxLid, seedNum);
        for(Tile tile : randomizedBoxLid){
            tileBag->addBack(tile);
        }
        std::cout << "Refill completed!" << std::endl;
    }
}

std::vector<Player*> GameEngine::getPlayers(){
    return players;
}

void GameEngine::applyWinLoss(){
    std::vector<Player*> winners;
    int highestScore;
    if(players.size()>0){
        highestScore = players[0]->getScore();
        for(Player* player:players){
            if(player->getScore()>highestScore){
                winners.clear();
                winners.push_back(player);
            } else if(player->getScore()==highestScore){
                winners.push_back(player);
            }
        }
        std::cout<<"Player "<<winners[0]->getName()<<" ";
        for(unsigned int i = 1; i != winners.size(); ++i){
            std::cout<<"and "<<winners[i]->getName()<<" ";
        }
        std::cout<<"wins!"<<std::endl;
    } else {
        std::cout<<"No one wins..."<<std::endl;
    }
}

void GameEngine::resetGame(){
    // Reset the load list
    loadList->clear();

    // Reset the input list
    inputList->clear();

    // Reset the tile bag
    tileBag->clear();

    // Reset the players
    players.clear();

    // Reset the factories
    for(BST_factory* factory : factories){
        delete factory;
    }
    factories.clear();

    loadLine = 0;
}

void GameEngine::printFactories(){
    std::cout<<"Factories:"<<std::endl;
        int count = 0;
        for(BST_factory* factory : factories) {
            std::cout<<count<<": ";
            factory->dfs();
            count++;
        }
        std::cout<<std::endl;
}

void GameEngine::printMosaic(Player* player){
    Pattern* pattern = player->getMosaic()->getPattern();
    Wall* wall = player->getMosaic()->getWall();
    std::vector<Tile> floor = player->getMosaic()->getFloor();

    std::cout<<"Mosaic for "<<player->getName()<<":"<<std::endl;
    for(int i = 0; i != ROW; ++i){
        std::cout<<i+1<<": ";

        // Print pattern part
        for(int j = 0; j != COLUMN-1-i; ++j){
            std::cout<<"  ";
        }
        for(Tile tile:pattern->getPatternLine(i)){
            std::cout<<convertToChar(tile)<<" ";
        }
        std::cout<<"|| ";

        // Print wall part
        for(int j = 0; j != COLUMN; ++j){
            std::cout<<convertToChar(wall->getWall()[j][i])<<" ";
        }
        std::cout<<std::endl;   
    }

    // Print floor part
    std::cout<<"(6)broken: ";
    for(Tile tile:floor){
        std::cout<<convertToChar(tile)<<" ";
    }
    std::cout<<std::endl;    
}

bool GameEngine::isTesting(){
    bool isTesting = (testMode&&loadLine!=loadList->size());
    return isTesting;
}

bool GameEngine::hasTiles(){
    bool hasTiles = false;
    for(BST_factory* factory : factories){
        if(!factory->isEmpty()){
            hasTiles = true;
        }
    }
    return hasTiles;
}

// Private

std::vector<Tile> GameEngine::takeTiles(unsigned int factoryIndex, Tile tile){
    std::vector<Tile> returnTiles;
    BST_factory* factory = factories.at(factoryIndex);
    BST_factory* centre = factories.at(0);
    int removeCounts = 0;
        if(factoryIndex == 0) {
            removeCounts = centre->remove(tile);
            for(int i = 0; i < removeCounts; i++) {
                returnTiles.push_back(tile);
            }
            if(centre->contains(FIRST_PLAYER)) {
                returnTiles.push_back(FIRST_PLAYER);
                centre->remove(FIRST_PLAYER);
            }

        } else {
            
            removeCounts = factory->remove(tile);
            
            for(int i = 0; i < removeCounts; i++) {
                returnTiles.push_back(tile); 
            }
            factory->remove(tile);
            factory->addRestTileToCenter(factory->getRoot(), centre);
            factory->clear();
        }

    return returnTiles;
}

void GameEngine::setWall(Player* player){
    player->getMosaic()->wallTiling();
    player->getMosaic()->resetFloor();
}

void GameEngine::updateScore(Player* player){
    player->setScore(player->getScore()+player->getMosaic()->getScore());
}

void GameEngine::recycleTiles(Player* player){
    std::vector<Tile> abandonList = player->getMosaic()->getAbandonList();
    for(Tile abandonTile:abandonList){
        if(seedNum > 0) {
            boxLid.push_back(abandonTile);
        }
        else {
            tileBag->addBack(abandonTile);
        }
    }
}

void GameEngine::processInput(Player* player){
    std::string input;

    if(loadMode){
        input = (*loadList)[loadLine];
        ++loadLine;
    } else if (std::getline(std::cin,input).eof()){
        std::cout<<"Good Bye"<<std::endl;
        exit(0);
    }

    // Turn command
    if(input.substr(0,COMMAND_LENGTH)==COMMAND_TURN && input.size()==COMMAND_TURN_LENGTH){

        try{
            // Check if factory index and pattern index is integer
            try{
                factoryIndex = std::stoi(input.substr(FACTORY_INDEX,1));
                patternIndex = std::stoi(input.substr(PATTERN_INDEX,1));
            }
            catch(std::invalid_argument& e){
                throw std::out_of_range("Invalid input - factory index and pattern line must be integer");
            }
            
            // Check if input tile type is valid
            tile = convertToEnum(input[TILE_INDEX]);

            if(factoryIndex>=factories.size()){
                throw std::out_of_range("Invalid factory - index out of range");
            } 
            else if (patternIndex==0||patternIndex>ROW+1){
                throw std::out_of_range("Invalid pattern line - index out of range");
            }

          else {
                if (!factories.at(factoryIndex)->contains(tile)) {
                    throw std::invalid_argument("Invalid Input - Factory has no this type of tiles");
                }

                if (tile == FIRST_PLAYER){
                    throw std::invalid_argument("Invalid tile - Cannot take first-player marker");
                }

            // If the chosen pattern line is not the floor 
            if (patternIndex!=ROW+1){
                if(player->getMosaic()->getPattern()->getLastTile(patternIndex)!=NO_TILE&&
                    player->getMosaic()->getPattern()->getLastTile(patternIndex)!=tile){
                    throw std::invalid_argument("Invalid pattern line - pattern line must have tiles with same color");
                } 
                else if (player->getMosaic()->getWall()->checkColor(tile,patternIndex)){
                    throw std::invalid_argument("Invalid pattern line - wall line has contained a same type of tile");
                } 
                else if (player->getMosaic()->getPattern()->getFirstTile(patternIndex)!=NO_TILE){
                    throw std::invalid_argument("Invalid pattern line - pattern line has been full");
                }
                else {
                    process = true;
                    inputList->push_back(input);
                }
            }
            else {
                process = true;
                inputList->push_back(input);
             }
          }
        } catch(std::out_of_range& e){
            throw e;
        } catch(std::invalid_argument& e){
            throw e;
        } catch(std::exception& e){
            throw e;
        }

    // Save command
    } else if(input.substr(0,COMMAND_LENGTH)==COMMAND_SAVE){
        try{
            saveGame(input.substr(COMMAND_LENGTH+1,input.size()-COMMAND_LENGTH+1));
        } catch(std::out_of_range& e){
            throw std::out_of_range("Invalid File Name");
        }
    } else {
        throw std::invalid_argument("Invalid input - unrecognized command");
    }
}

void GameEngine::saveGame(std::string name){
    if(name.size()==0){
        std::cout<<"Invalid File Name"<<std::endl;
    } else {
        std::fstream file(name, std::fstream::out | std::ios_base::trunc);
        for(std::string inputLine:*inputList){
            file.write(inputLine.c_str(),inputLine.size());
            file.put('\n');
        }
        file.close();
        std::cout<<"Game successfully saved to '"<<name<<"'"<<std::endl;
    }
}

char GameEngine::convertToChar(Tile tile){
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

Tile GameEngine::convertToEnum(char tile){
    Tile enumTile = NO_TILE;
    if(tile == R){
        enumTile = RED;
    } else if(tile == Y){
        enumTile = YELLOW;
    } else if(tile == B){
        enumTile = DARK_BLUE;
    } else if(tile == L){
        enumTile = LIGHT_BLUE;
    } else if(tile == U){
        enumTile = BLACK;
    } else if(tile == F){
        enumTile = FIRST_PLAYER;
    } else if(tile == N){
        enumTile = NO_TILE;
    } else {
        throw std::invalid_argument("Invalid tile - tile type not found");
    }
    return enumTile;
}

void GameEngine::initTileBag(){
    std::string tiles;
    Tile tile;
    int tilesCount[TILE_TYPES] = {0};

    // Load tile bag
    if(!loadList->empty()){
        if((*loadList)[0].substr(0, 1) == "#") {
            try {
                seedNum = std::stoi((*loadList)[0].substr(1, (*loadList)[0].length()-1));
                if(seedNum == 0) {
                  throw std::invalid_argument("Invalid seed has been found, seed cannot be negative number, string or 0");
                }
            }
            catch(std::exception& e) {
                throw std::invalid_argument("Invalid seed has been found, seed cannot be negative number, string or 0");
            }

            if(seedNum > 0) {
                std::string RandomTilesInLoad = DEFAULT_TILE_BAG;
                tiles = shuffledTileBag(RandomTilesInLoad, seedNum);
                ++loadLine;
            }
        }
        else {
            tiles = (*loadList)[0];
            ++loadLine;
        }
    }
    else if(seedNum > 0) {
        std::string randomList = DEFAULT_TILE_BAG;
        tiles = shuffledTileBag(randomList, seedNum);
    }
    else {
        tiles = DEFAULT_TILE_BAG;
    }

    // Add tiles to tile bag linked list
    try{
        for(char tileChar:tiles){
            tile = convertToEnum(tileChar);
            tileBag->addBack(tile);
            ++tilesCount[tile];
        }
    } catch(std::invalid_argument& e){
        std::string error = e.what();
        throw std::invalid_argument("error in line "+std::to_string(loadLine)+" | "+error);
    }

    // Check if the size of tile bag is valid
    for(int t:tilesCount){
        if(t!=EACH_COLOR_TILES){
            throw std::invalid_argument("error in line "+std::to_string(loadLine)+" | Invalid tile bag");
        }
    }
    
    // Save tile bag
    if(seedNum > 0) {
        std::string saveSeed = std::to_string(seedNum);
        inputList->push_back("#"+saveSeed);
    }
    else {
        inputList->push_back(tiles);
    }
}

void GameEngine::initPlayers(){
    std::string name;

    while(players.size() < DEFAULT_PLAYERS) {
        if(!loadList->empty()){
            name = loadList->at(loadLine);
            ++loadLine;
            if (name.size() == 0 || name.size() > 20){
                std::string error = "Invalid Name";
                throw std::invalid_argument("error in line "+std::to_string(loadLine)+" | "+error);
            }
            checkLoad();
        } else {
            std::cout << "Enter a name for player " << players.size()+1 << std::endl;
            do {
                std::cout << "> ";
                if(std::getline(std::cin,name).eof()){
                    std::cout<<"Good Bye"<<std::endl;
                    exit(0);
                } else if (name.size() == 0){
                    std::cout << "Invalid input - Name can not be empty, pls input name" << std::endl;
                } else if(name.size() > 20) {
                    std::cout << "Invalid input - Name can not be over 20 characters " << std::endl;
                }
            }
            while(name.size() == 0 || name.size() > 20);
        }
        players.push_back(new Player(name));
        inputList->push_back(name);
    }    
}

void GameEngine::checkLoad(){
    if(loadLine==loadList->size()&&!testMode){
        std::cout<<std::endl;
        std::cout<<"Azul game successfully loaded"<<std::endl;
        std::cout<<std::endl;
    }
}

template <typename T>
T GameEngine::shuffledTileBag(T tiles, unsigned int seed) {
    shuffle(tiles.begin(), tiles.end(), std::default_random_engine(seed));
    return tiles;
}