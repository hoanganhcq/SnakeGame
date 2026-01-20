#pragma once
#include <string>

class Player {
private:
    std::string name;
    int score;

    bool saved;
public:
    Player(std::string, int score);
    Player();
    ~Player();

    void setName(std::string name);
    void setScore(int score);

    std::string getName() const;
    int getScore() const;

    bool isSaved() const;
    void savedPlayer();
};