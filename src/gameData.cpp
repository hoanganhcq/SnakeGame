#include "gameData.h"

GameData::GameData() {
    filePath = "assets/data/leaderboard.txt";
    load();
}


GameData::~GameData() {
    save();
}


void GameData::load() {
    leaderboard.clear();
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string name;
        int score;

        while (file >> name >> score) {
            leaderboard.push_back(Player(name, score));
        }
        file.close();
    }
}


void GameData::save() {
    std::ofstream file(filePath);
    if (file.is_open()) {
        for (const auto& p : leaderboard) {
            file << p.getName() << " " << p.getScore() << std::endl;
        }
        file.close();
    }
}


void GameData::updateLeaderBoard(Player newPlayer) {
    bool playerExists = false;

    for (auto& p : leaderboard) {
        if (p.getName() == newPlayer.getName()) {
            playerExists = true;

            if (newPlayer.getScore() > p.getScore()) {
                p.setScore(newPlayer.getScore());
            }

            break;
        }
    }

    if (!playerExists) {
        leaderboard.push_back(newPlayer);
    }

    std::sort(leaderboard.begin(), leaderboard.end(),
        [](const Player& a, const Player& b) {
            return a.getScore() > b.getScore();
        }
    );

    if (leaderboard.size() > MAX_RECORDS) {
        leaderboard.resize(MAX_RECORDS);
    }
    save();
}


const std::vector<Player>& GameData::getLeaderboard() const {
    return leaderboard;
}


int GameData::getBestScore() const {
    if (leaderboard.empty()) return 0;
    return leaderboard[0].getScore();
}