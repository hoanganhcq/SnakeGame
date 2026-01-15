#include "food.h"

Food::Food() {
    setTexture("food");
    dest.w = GRID_SIZE;
    dest.h = GRID_SIZE;

    col_x = 0;
    row_y = 0;
}


Food::~Food() {
    // TextureManager did
}


void Food::respawn(int screenWidth, int screenHeight) {
    int maxCols = screenWidth / GRID_SIZE;
    int maxRows = screenHeight / GRID_SIZE;

    col_x = rand() % maxCols; // 0 -> (max - 1)
    row_y = rand() % maxRows;
}


void Food::render(SDL_Renderer* renderer) {
    dest.x = col_x * GRID_SIZE;
    dest.y = row_y * GRID_SIZE;

    Object::render(renderer);
}


int Food::getCol() const {
    return col_x;
}


int Food::getRow() const {
    return row_y;
}