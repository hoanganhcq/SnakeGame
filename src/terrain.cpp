#include "terrain.h"

Terrain::Terrain() {
    texture = TextureManager::Instance()->getTexture("terrain_wall");
    loadTerrain("assets/data/terrain.txt", 30, 30);

    startCol = 0;
    startRow = 6;

    src.x = 0;
    src.y = 0;
    if (texture != NULL) {
        SDL_QueryTexture(texture, NULL, NULL, &src.w, & src.h);
    } else {
        src.w = 32;
        src.h = 32;
    }

    dest.w = GRID_SIZE;
    dest.h = GRID_SIZE;
}


Terrain::~Terrain() {

}


void Terrain::loadTerrain(std::string path, int rows, int cols) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Failed to open terrain file" << std::endl;
        return;
    }

    mapData.resize(rows);
    for (int i = 0; i < rows; i++) {
        mapData[i].resize(cols);
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            file >> mapData[row][col];
        }
    }

    file.close();
    std::cout << "Terrain loaded sucessfully!" << std::endl;
}


void Terrain::render(SDL_Renderer* renderer) {
    for (int row = 0; row < (int)mapData.size(); row++) {
        for (int col = 0; col < (int)mapData[row].size(); col++) {
            if (mapData[row][col] == 1) {
                dest.x = (col + startCol) * GRID_SIZE;
                dest.y = (row + startRow) * GRID_SIZE;

                SDL_RenderCopy(renderer, texture, &src, &dest);
            }
        }
    }
}


int Terrain::getTile(int row, int col) const {
    int mapRow = row - startRow;
    int mapCol = col - startCol;

    if (mapRow < 0 || mapRow >= (int)mapData.size()) return 0;
    if (mapCol < 0 || mapCol >= (int)mapData[0].size()) return 0;

    return mapData[mapRow][mapCol];
}


int Terrain::getCols() {
    return (int)mapData.size();
}


int Terrain::getRows() {
    return mapData.empty() ? 0 : (int)mapData[0].size();
}


int Terrain::getStartCol() const {
    return startCol;
}


int Terrain::getStartRow() const {
    return startRow;
}