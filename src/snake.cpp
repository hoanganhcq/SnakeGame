#include "snake.h"

Snake:: Snake() {
    headTexture = TextureManager::Instance()->getTexture("snake_head");
    bodyTexture = TextureManager::Instance()->getTexture("snake_body");

    // init with 3 segments
    body.push_back({10, 10, 1, 0});
    body.push_back({9, 10, 1, 0});
    body.push_back({8, 10, 1, 0});
    body.push_back({7, 10, 1, 0});

    dirX = 1;
    dirY = 0;
    nextDirX = 1;
    nextDirY = 0;

    delay = 360;
    moveTimer = 0;

    growing = false;
}


Snake::~Snake() {
    body.clear();
}


void Snake::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (dirY != 1) {
                    nextDirX = 0;
                    nextDirY = -1;
                }
                break;
            case SDLK_DOWN:
                if (dirY != -1) {
                    nextDirX = 0;
                    nextDirY = 1;
                }
                break;
            case SDLK_LEFT:
                if (dirX != 1) {
                    nextDirX = -1;
                    nextDirY = 0;
                }
                break;
            case SDLK_RIGHT:
                if (dirX != -1) {
                    nextDirX = 1;
                    nextDirY = 0;
                }
                break;
        }
    }
}


void Snake::update() {
    moveTimer++;
    if (moveTimer < delay) return;
    moveTimer = 0;

    dirX = nextDirX;
    dirY = nextDirY;

    int newCol = body.front().col_x + dirX;
    int newRow = body.front().row_y + dirY;

    SnakeSegment newHead = {newCol, newRow, dirX, dirY};
    body.push_front(newHead);

    if (!growing) {
        body.pop_back();
    } else {
        growing = false;
    }
}


void Snake::grow() {
    growing = true;
}


void Snake::render(SDL_Renderer* renderer) {
    SDL_Rect segmentDest = {0, 0, GRID_SIZE, GRID_SIZE};

    for (size_t i = 0; i < body.size(); i++) {
        SnakeSegment& seg = body[i];

        segmentDest.x = seg.col_x * GRID_SIZE;
        segmentDest.y = seg.row_y * GRID_SIZE;

        double angle = 0;
        if (seg.dirX == -1) angle = 180;
        else if (seg.dirY == 1) angle = 90;
        else if (seg.dirY == -1) angle = -90;

        SDL_Texture* currentTexture = (i == 0) ? headTexture : bodyTexture;

        SDL_RenderCopyEx(renderer, currentTexture, NULL, &segmentDest, angle, NULL, SDL_FLIP_NONE);
    }
}


std::deque<SnakeSegment> Snake::getBody() {
    return body;
}


int Snake::getHeadCol() {
    return body.front().col_x;
}


int Snake::getHeadRow() {
    return body.front().row_y;
}