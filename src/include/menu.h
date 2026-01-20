#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "button.h"
#include "inputBox.h"
#include "textureManager.h"

class Menu {
private:
    TTF_Font* font;        
    TTF_Font* titleFont;  

    // UI Components
    Button* startButton;
    Button* exitButton;

    InputBox* inputBox;

    SDL_Texture* titleTexture;
    SDL_Rect titleRect;

    SDL_Texture* bg_texture;

public:
    Menu(SDL_Renderer* renderer, int screenWidth, int screenHeight, TTF_Font* globalFont);
    ~Menu();

    void render(SDL_Renderer* renderer);
    
    int handleEvent(SDL_Event* e, SDL_Renderer* renderer); // 1 (Start), 2 (Exit)

    std::string getPlayerName() const;
};