#pragma once
#include "object.h"
#include <deque>

struct SnakeSegment {
    int x, y;
    int dirX, dirY;
};


class Snake : public Object {
private:
    const int SEGMENT_SIZE = 20;
    std::deque<SnakeSegment> body;
    
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;

    int dirX, dirY, nextDirX, nextDirY;
    int delay;
    int moveTimer;

    bool growing;
public:
    Snake();
    ~Snake();

    void update() override;
    void render(SDL_Renderer* renderer) override;

    void handleInput(SDL_Event& event);
    void grow();
};