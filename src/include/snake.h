#pragma once
#include "object.h"
#include <deque>

struct SnakeSegment {
    int x, y;
    int dirX, dirY;
};


class Snake : public Object {
private:
    std::deque<SnakeSegment> body;
    
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;

    int dirX, dirY, nextDirX, nextDirY;
    bool growing;
public:
    Snake();
    ~Snake();

    void update() override;
    void render(SDL_Renderer* renderer) override;

    void handleInput(SDL_Event& event);
    void grow();
};