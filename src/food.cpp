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


void Food::respawn(Terrain* pTerrain, Snake* pSnake) {
    if (!pTerrain || !pSnake) return;

    bool validPosition = false;

    int mapCols = pTerrain->getCols();
    int mapRows = pTerrain->getRows();
    int offX = pTerrain->getStartCol();
    int offY = pTerrain->getStartRow();

    while (!validPosition) {
        int randCol = rand() % mapCols;
        int randRow = rand() % mapRows;

        col_x = offX + randCol;
        row_y = offY + randRow;

        if (pTerrain->getTile(row_y, col_x) == 1) continue;

        bool onSnake = false;
        const std::deque<SnakeSegment> body = pSnake->getBody();

        if ((int)body.size() >= mapCols * mapRows) return;

        for (const auto& segment : body) {
            if (segment.col_x == col_x && segment.row_y == row_y) {
                onSnake = true;
                break;
            }
        }

        if (onSnake) {
            continue;
        }

        validPosition = true;
    }
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