#include<iostream>
#include<string>
#include <exception>
#include <stdexcept>

#include"Player.h"
#include "GameEngine.h"

void displayMenu();
void newGame();
void loadGame();
void showCredit();
void quit();
int processInput();
void processChoice(int choice);
void roundPlay(bool testMode);
void testGame(std::string fileName);

GameEngine* gameEngine;
int playersCount;
int firstPlayer;
int choice;
int seedNum = 0;
bool testMode;

int main(int argc, char** argv){
	gameEngine = new GameEngine();
	
	// Test mode
	if(argc == COMMAND_TEST_LENGTH&&std::string(argv[1])==COMMAND_TEST){
		std::string fileName = argv[argc-1];
		testMode = true;
		testGame(fileName);
	}

	//Enable randomness
	else if(argc == COMMAND_TEST_LENGTH && std::string(argv[1])==COMMAND_RANDOMNESS) {
		std::string seed(argv[argc-1]);

		try {
			seedNum = std::stoi(seed);
			testMode = false;
			if(seedNum <= 0) {
				throw std::invalid_argument("Invalid Input - Seed cannot be string, negative number or 0");
			}
			else {
				displayMenu();
			}
		}
		catch(std::exception& e) {
			std::cout << "Invalid Input - Seed cannot be string, negative number or 0" << std::endl;
		}
	}

	// Normal mode
	else if(argc == 1){
		testMode = false;
		displayMenu();
	}
	else{
		std::cout<<"Invalid Argument"<<std::endl;
	}
	
	delete gameEngine;
	return EXIT_SUCCESS;
}

void displayMenu() {
	std::cout<<"Welcome to Azul!"<<std::endl;
	std::cout<<"------------------------------"<<std::endl;
	std::cout<<std::endl;   
	std::cout<<std::endl;   
	std::cout<<"Menu"<<std::endl;
	std::cout<<"----"<<std::endl;
	std::cout<<"1.New Game";
	if(seedNum > 0) {
		std::cout << " (Randomness On) ";
	}
	else {
		std::cout << " (Randomness off) ";
	}
	std::cout << std::endl;
	std::cout<<"2.Load Game"<<std::endl;
	std::cout<<"3.Credits (Show student information)"<<std::endl;
	std::cout<<"4.Quit"<<std::endl;
	std::cout<<std::endl;

	do {
		choice = processInput();
	} while(choice <= 0 || choice > 4);
	processChoice(choice);
}

void newGame() {
	std::string name;

	std::cout<<"Starting a new game"<<std::endl;
	firstPlayer = 0;

	// Initialize the game
	gameEngine->initGame(testMode, nullptr, seedNum);
	std::cout<<std::endl;
	std::cout <<"Let's Play!"<< std::endl;
	std::cout<<std::endl;

	// Start game round
	roundPlay(testMode);

	// Print result
	gameEngine->applyWinLoss();
}

void loadGame() {
	std::string fileName;
	bool process;

	std::cout<<"Enter the filename from which load a game"<<std::endl;
	do{
		process = true;
		firstPlayer = 0;
		try{
			std::cout<<"> ";
			if(std::getline(std::cin,fileName).eof()) {
				std::cout<<"Good Bye"<<std::endl;
				exit(0);
			}
			gameEngine->initGame(testMode, &fileName, seedNum);

			// Start game round
			roundPlay(testMode);
		}
		catch(std::exception& e){
			process = false;
			gameEngine->resetGame();
			std::cout<<e.what()<<std::endl;
		}
	} while(!process);

	// Print result
	gameEngine->applyWinLoss();
}

void showCredit() {
	std::ifstream credit("credit");
	std::string info;
	while(getline(credit, info)) {
		std::cout << info << std::endl;
	}
	displayMenu();
}

void quit() {
	std::cout<<"Good Bye"<<std::endl;
    exit(0);
}

int processInput() {
	std::string input;
	choice = 0;
	std::cout<<"> ";
	if(std::getline(std::cin,input).eof()){
        std::cout<<"Good Bye"<<std::endl;
        exit(0);
    }
	else {
		try {
			choice = std::stoi(input.substr(0));
			if(choice <= 0 || choice > 4) {
				std::cout << "No options for choice - " << choice << std::endl;
			}
		}
		catch(std::exception& e) {
			std::cout << "Invalid input - Please enter Integer to make your choice! " << std::endl;
		}
	}
	return choice;
}

void processChoice(int choice) {
	if(choice==1) {
		newGame();
	}
	else if(choice==2) {
		loadGame();
	}
	else if(choice==3) {
		showCredit();
	}
	else if(choice==4){
		quit();
	}
}

void roundPlay(bool testMode){
	int gameRound = 1;
	bool gameContinue;
	bool testContinue;
	do {
		// Tile-taking phase
		firstPlayer = gameEngine->startTurn(firstPlayer);

		// Update game status
		gameContinue = (!testMode && gameRound < 20);
		testContinue = (testMode && gameRound < 20 && gameEngine->isTesting());

		// Wall-tiling phase, Score-update phase, Factory-reset phase, unless finish testing
		if(!gameEngine->hasTiles()){
			gameEngine->endRound();
			gameEngine->resetFactories();
		}

		gameRound++;
	} while(gameContinue||testContinue);
}

void testGame(std::string fileName){
	firstPlayer = 0;

	try{
		gameEngine->initGame(true,&fileName, 0);
		roundPlay(testMode);
		
		// Print result
		gameEngine->printFactories();
		std::cout<<std::endl;
		for(Player* player:gameEngine->getPlayers()){
			std::cout<<"Score for Player "<<player->getName()<<": "<<player->getScore()<<std::endl;
			gameEngine->printMosaic(player);
			std::cout<<std::endl;
		}
	}
	catch(std::exception& e){
		std::cout<<e.what()<<std::endl;
	}
}