#pragma once
#include "textureManager.h"
#include <SDL2/SDL.h>
#include <string>

class Object {
protected:
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* texture;

    double angle;
    SDL_RendererFlip flip;
public:
    Object();
    virtual ~Object() {}

    virtual void update();
    virtual void render(SDL_Renderer* renderer);

    SDL_Rect& getSrc();
	SDL_Rect& getDest();

    void setSrc(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);

    void setTexture(std::string id);
};