#pragma once
#include "textureManager.h"
#include "snake.h"
#include "food.h"
#include "terrain.h"
#include "hud.h"
#include "gameData.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


enum class GameState {
    MENU = 0,
    PLAYING = 1,
    PAUSE = 2,
    GAME_OVER = 3
};


class GameLoop {
private:
    const int WIDTH = 600;
    const int HEIGHT = 720;

    GameState currentState = GameState::PLAYING; // init in MENU then

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event = {};

    bool running;

    Snake* snake;
    Food* food;
    Terrain* terrain;
    GameData* gameData;
    HUD* hud;
    Player* player;
    std::string playerName;

    TTF_Font* globalFont;
    
public:
    GameLoop();

    bool initialize();
    void handleEvents();
    void update();
    void render();

    void reset();

    bool isRunning();
    void clean();
};