#include "gameLoop.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[]) {
    GameLoop* game = new GameLoop();
    
    if (!game->initialize()) {
        std::cout << "Failed to initialize the game!\n";
        delete game;
        return -1;
    }

    while (game->isRunning()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    delete game;
    return 0;
}