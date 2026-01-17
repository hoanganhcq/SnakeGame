#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Button {
private:
    SDL_Rect rect;         
    SDL_Texture* texture;  
    SDL_Rect textRect;      
    
    SDL_Color textNormalColor; 
    SDL_Color textHoverColor;   

    SDL_Color bgNormalColor;
    SDL_Color bgHoverColor;

    bool isHovered;
    int paddingX = 20; 
    int paddingY = 10;
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, std::string text, int x, int y);
    Button();
    ~Button();

    void render(SDL_Renderer* renderer);
    bool handleEvent(SDL_Event* e);
    
    int getWidth() const { return rect.w; }
    int getHeight() const { return rect.h; }
    void setPosition(int x, int y);
};