#include "player.h"

Player::Player(std::string name, int score) {
    this->name = name;
    this->score = score;
    this->saved = false;
}



Player::Player() {
    name = "unknown";
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


bool Player::isSaved() const {
    return saved;
}


void Player::savedPlayer() {
    if (!saved) {
        saved = true;
    }
}