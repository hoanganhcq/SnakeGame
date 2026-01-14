#include "gameLoop.h"
#include <iostream>

GameLoop::GameLoop() {
    window = NULL;
    renderer = NULL;
    running = false;


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

    running = true;
    return true;
}


void GameLoop::handleEvents() {
    SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            running = false;
            return;
        }
    
}


void GameLoop::update() {

}


void GameLoop::render() {
    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);
}


bool GameLoop::isRunning() {
    return running;
}

void GameLoop::clean() {

    TextureManager::Instance()->clean();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    renderer = NULL;
    window   = NULL;

    IMG_Quit();
    SDL_Quit();
}