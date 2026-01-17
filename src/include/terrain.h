#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "textureManager.h"

class Terrain {
private:
    SDL_Texture* texture;
    SDL_Rect src, dest;

    std::vector<std::vector<int>> mapData;

    const int GRID_SIZE = 20;

    int startCol, startRow;
public:
    Terrain();
    ~Terrain();

    void loadTerrain(std::string path, int rows, int cols);
    void render(SDL_Renderer* renderer);
    int getTile(int row, int col) const;

    int getCols();
    int getRows();
    int getStartCol() const;
    int getStartRow() const;
};