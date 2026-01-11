#include "textureWrapper.h"
#include <SDL2/SDL_image.h>

TextureWrapper::TextureWrapper() {
    texture = NULL;
}


TextureWrapper::~TextureWrapper() {
    free();
}


bool TextureWrapper::loadFromFile(SDL_Renderer* renderer, std::string path) {
    free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        std::cout <<"cannot create surface " << "SDL_image Error: " << IMG_GetError() << std::endl;
    }

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
        std::cout << "Cannot create Texture from Surface: " << SDL_GetError() << std::endl;
    } else {
        texture = newTexture;
    }

    return texture != NULL;
}


SDL_Texture* TextureWrapper::getTexture() {
    return this->texture;
}


void TextureWrapper::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}