#include "gameLoop.h"
#include "collision.h"
#include <iostream>

GameLoop::GameLoop() {
    window = NULL;
    renderer = NULL;
    running = false;

    snake = NULL;
    food = NULL;
    terrain = NULL;
    gameData = NULL;
    hud = NULL;
    player = NULL;
}

bool GameLoop::initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        "Snake Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        running = false;
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);

    // Load all Images
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (!TextureManager::Instance()->loadFromList(renderer, "assets/data/textures.txt")) {
        std::cout << "Failed to load textures!" << std::endl;
        return false;
    }

    terrain = new Terrain();

    snake = new Snake();

    gameData = new GameData();

    hud = new HUD();

    food = new Food();
    food->respawn(terrain, snake);

    player = new Player("Guest", 0);


    running = true;
    return true;
}


void GameLoop::handleEvents() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        running = false;
        return;
    }
    
    snake->handleInput(event);
}


void GameLoop::update() {
    snake->update();

    if (Collision::check(snake, food)) {
        std::cout << "Yummy!\n";
        snake->grow();
        food->respawn(terrain, snake);
        player->setScore(player->getScore() + 10);
    }

    if (Collision::checkSelf(snake)) {
        std::cout << "Game Over: Bitting tail!\n";
        running = false;
    }

    if (Collision::checkTerrain(snake, terrain)) {
        std::cout << "Game Over\n";
        running = false;
    }

    if (player->getScore() > gameData->getBestScore()) {
        gameData->updateLeaderBoard(*player);
    }

    hud->update(player->getScore(), gameData->getBestScore(), renderer);
}


void GameLoop::render() {
    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (terrain) terrain->render(renderer);
    if (snake) snake->render(renderer);
    if (food) food->render(renderer);
    if (hud) hud->render(renderer);

    SDL_RenderPresent(renderer);
}


bool GameLoop::isRunning() {
    return running;
}

void GameLoop::clean() {

    if (snake) {
        delete snake;
        snake = NULL;
    }

    if (terrain) {
        delete terrain;
        terrain = NULL;
    }

    if (gameData) {
        delete gameData;
        gameData = NULL;
    }

    if (hud) {
        delete hud;
        hud = NULL;
    }

    if (player) {
        delete player;
        player = NULL;
    }

    TextureManager::Instance()->clean();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    renderer = NULL;
    window   = NULL;

    IMG_Quit();
    SDL_Quit();
}