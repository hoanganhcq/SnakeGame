#include "snake.h"

Snake:: Snake() {
    headTexture = TextureManager::Instance()->getTexture("snake_head");
    bodyTexture = TextureManager::Instance()->getTexture("snake_body");

    // init with 3 segments
    body.push_back({10, 10, 1, 0});
    body.push_back({9, 10, 1, 0});
    body.push_back({8, 10, 1, 0});
}


Snake::~Snake() {
    body.clear();
}


void Snake::update() {

}


void Snake::render(SDL_Renderer* renderer) {
    SDL_Rect segmentDest = {0, 0, 32, 32};

    for (size_t i = 0; i < body.size(); i++) {
        SnakeSegment& seg = body[i];

        segmentDest.x = seg.x * 32;
        segmentDest.y = seg.y * 32;

        double angle = 0;
        if (seg.dirX == -1) angle = 180;
        else if (seg.dirY == 1) angle = 90;
        else if (seg.dirY == -1) angle = -90;

        SDL_Texture* currentTexture = (i == 0) ? headTexture : bodyTexture;

        SDL_RenderCopyEx(renderer, currentTexture, NULL, &segmentDest, angle, NULL, SDL_FLIP_NONE);
    }
}