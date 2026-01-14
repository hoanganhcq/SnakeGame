#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

class TextureManager {
private:
    std::map<std::string, SDL_Texture*> textureMap;
    static TextureManager* instance;

    // Private Constructor (Singleton)
    TextureManager();
public:
    ~TextureManager();

    static TextureManager* Instance();

    bool loadFromList(SDL_Renderer* renderer, std::string listFilePath);

    SDL_Texture* getTexture(std::string id);
    
    void clean();
};