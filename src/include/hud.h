#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class HUD {
private:
    TTF_Font* font;
    SDL_Color textColor;

    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;

    SDL_Texture* bestScoreTexture;
    SDL_Rect bestScoreRect;

    int currentScore;
    int currentBestScore;
    
    void loadText(SDL_Renderer* renderer, int value, bool isBest); // load texture from string
public:
    HUD(TTF_Font* globalFont);
    ~HUD();

    void update(int score, int bestScore, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
};