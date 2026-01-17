#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "button.h"

class Menu {
private:
    TTF_Font* font;        
    TTF_Font* titleFont;  

    // UI Components
    Button* startButton;
    Button* exitButton;

    SDL_Texture* titleTexture;
    SDL_Rect titleRect;

public:
    Menu(SDL_Renderer* renderer, int screenWidth, int screenHeight, TTF_Font* globalFont);
    ~Menu();

    void render(SDL_Renderer* renderer);
    
    int handleEvent(SDL_Event* e); // 1 (Start), 2 (Exit)
};