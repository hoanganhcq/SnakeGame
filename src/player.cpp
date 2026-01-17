#include "player.h"

Player::Player(std::string name, int score) {
    this->name = name;
    this->score = score;
}



Player::Player() {
    name = "unknow";
    score = 0;
}


Player::~Player() {

}


void Player::setName(std::string name) {
    this->name = name;
}

void Player::setScore(int score) {
    this->score = score;
}

std::string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}