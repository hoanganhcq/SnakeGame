#pragma once
#include "player.h"
#include <vector>
#include <fstream>
#include <algorithm>


class GameData {
private:
    std::string filePath;
    std::vector<Player> leaderboard;
    const size_t MAX_RECORDS = 5;
public:
    GameData();
    ~GameData();

    void load();
    void save();

    void updateLeaderBoard(Player newPlayer);
    
    const std::vector<Player>& getLeaderboard() const;
    int getBestScore() const;
};