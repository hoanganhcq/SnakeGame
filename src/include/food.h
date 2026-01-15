#pragma once
#include "object.h"
#include <cstdlib>
#include <ctime>

class Food : public Object {
private:
    const int GRID_SIZE = 20;
    int col_x, row_y;

public:
    Food();
    ~Food();

    void respawn(int screenWidth, int screenHeight);

    void render(SDL_Renderer* renderer) override;

    int getCol() const;
    int getRow() const;
};