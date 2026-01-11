#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class TextureWrapper {
private:
    SDL_Texture* texture;
public:
    TextureWrapper();
    ~TextureWrapper();
    
    bool loadFromFile(SDL_Renderer* renderer, std::string path);
    SDL_Texture* getTexture();
    void free();
};