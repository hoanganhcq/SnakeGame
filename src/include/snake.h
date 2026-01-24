#pragma once
#include "object.h"
#include "soundManager.h"
#include <deque>

struct SnakeSegment {
    int col_x, row_y;
    int dirX, dirY;
};


class Snake : public Object {
private:
    const int GRID_SIZE = 20;
    std::deque<SnakeSegment> body;
    
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Texture* tailTexture;

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

    std::deque<SnakeSegment> getBody();
    int getHeadCol();
    int getHeadRow();
};