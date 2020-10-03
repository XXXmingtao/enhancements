#include "Player.h"

Player::Player(std::string name){
    this->name = name;
    score = 0;
    mosaic = new Mosaic();
}

Player::~Player(){
    delete mosaic;
}

std::string Player::getName(){
    return this->name;
}

int Player::getScore(){
    return this->score;
}

void Player::setName(std::string name){
    this->name = name;
}

void Player::setScore(int score){
    this->score = score;
}

Mosaic* Player::getMosaic(){
    return mosaic;
}