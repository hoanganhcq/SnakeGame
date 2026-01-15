#pragma once
#include "snake.h"
#include "food.h"

class Collision {
public:
    static bool check(Snake* pSnake, Food* pFood);
    static bool checkSelf(Snake* pSnake);
    static bool checkBounds(Snake* pSnake, int x0, int y0, int width, int height);
};