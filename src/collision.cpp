#include "collision.h"

bool Collision::check(Snake* pSnake, Food* pFood) {
    if (!pSnake || !pFood) return false;

    return (pSnake-> getHeadCol() == pFood->getCol() && 
            pSnake->getHeadRow() == pFood->getRow());
}


bool Collision::checkSelf(Snake* pSnake) {
    if (!pSnake) return false;

    const std::deque<SnakeSegment> body = pSnake->getBody();

    if (body.size() < 5) return false;

    int headCol = pSnake->getHeadCol();
    int headRow = pSnake->getHeadRow();

    for (size_t i = 1; i < body.size(); i++) {
        if (headCol == body[i].col_x && headRow == body[i].row_y) {
            return true;
        }
    }

    return false;
}


bool Collision::checkTerrain(Snake* pSnake, Terrain* pTerrain) {
    int head_col = pSnake->getHeadCol();
    int head_row = pSnake->getHeadRow();

    if (pTerrain->getTile(head_row, head_col) == 1) return true;

    return false;
}


bool Collision::checkTerrain(Food* pFood, Terrain* pTerrain) {
    int food_col = pFood->getCol();
    int food_row = pFood->getRow();

    if (pTerrain->getTile(food_row, food_col) == 1) return true;

    return false;
}