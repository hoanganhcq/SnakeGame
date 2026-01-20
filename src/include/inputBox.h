#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class InputBox {
private:
    SDL_Rect rect;          
    SDL_Color borderColor;  
    SDL_Color textColor;    
    SDL_Color backgroundColor;
    
    std::string placeholder; // "Enter your name"
    SDL_Color placeholderColor;

    std::string text;       
    SDL_Texture* texture;   
    SDL_Rect textRect;      
    
    bool isFocused;         
    int maxLength;         

    void updateTexture(SDL_Renderer* renderer, TTF_Font* font);

public:
    InputBox(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h);
    ~InputBox();

    void handleEvent(SDL_Event* e, SDL_Renderer* renderer, TTF_Font* font);
    void render(SDL_Renderer* renderer);

    std::string getText() const;
};