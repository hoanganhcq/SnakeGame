#include "textureManager.h"
#include <SDL2/SDL_image.h>


TextureManager* TextureManager::instance = 0;

TextureManager::TextureManager() {
    textureMap = {};
}


TextureManager::~TextureManager() {
    clean();
}


TextureManager* TextureManager::Instance() {
    if (instance == 0) {
        instance = new TextureManager();
    }
    return instance;
}


bool TextureManager::loadFromList(SDL_Renderer* renderer, std::string listFilePath) {
    std::ifstream file(listFilePath);
    
    if (!file.is_open()) {
        std::cout << "Cannot open config file: " << listFilePath << std::endl;
        return false;
    }

    std::string id;
    std::string path;

    while (file >> id >> path) {
        SDL_Surface* tempSurface = IMG_Load(path.c_str());

        if (tempSurface == NULL) {
            std::cout << "Loading Image Error (" << id << "): " << IMG_GetError() << std::endl;
            continue; 
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        if (texture != NULL) {
            textureMap[id] = texture;
            std::cout << "Loaded: " << id << " from " << path << std::endl;
        }
    }

    file.close();
    return true;
}


SDL_Texture* TextureManager::getTexture(std::string id) {
    if (textureMap.find(id) == textureMap.end()) {
        std::cout << "Texture ID not found: " << id << std::endl;
        return NULL;
    }
    return textureMap[id];
}


void TextureManager::clean() {
    for (auto const& [id, texture] : textureMap) {
        SDL_DestroyTexture(texture);
    }
    
    textureMap.clear();
    std::cout << "All textures have been released\n"; 
}