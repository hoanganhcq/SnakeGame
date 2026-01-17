#pragma once
#include "snake.h"
#include "food.h"
#include "terrain.h"

class Collision {
public:
    static bool check(Snake* pSnake, Food* pFood);
    static bool checkSelf(Snake* pSnake);
    static bool checkTerrain(Snake* pSnake, Terrain* pTerrain);
    static bool checkTerrain(Food* pFood, Terrain* pTerrain);
};