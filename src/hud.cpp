#include "hud.h"

HUD::HUD(TTF_Font* globalFont) {
    font = globalFont;

    textColor = { 255, 255, 255, 255}; // white
    
    scoreTexture = NULL;
    bestScoreTexture = NULL;
    currentScore = -1;
    currentBestScore = -1;
}


HUD::~HUD() {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (bestScoreTexture) SDL_DestroyTexture(bestScoreTexture);
    if (font) TTF_CloseFont(font);
    TTF_Quit();
}


void HUD::loadText(SDL_Renderer* renderer, int value, bool isBest) {
    std::string text = (isBest ? "Best: " : "Score: ") + std::to_string(value);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (!textSurface) return;

    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (isBest) {
        if (bestScoreTexture) SDL_DestroyTexture(bestScoreTexture);
        bestScoreTexture = newTexture;
        bestScoreRect.w = textSurface->w;
        bestScoreRect.h = textSurface->h;
        bestScoreRect.x = 240;
        bestScoreRect.y = 10;
    } else {
        if (scoreTexture) SDL_DestroyTexture(scoreTexture);
        scoreTexture = newTexture;
        scoreRect.w = textSurface->w;
        scoreRect.h = textSurface->h;
        scoreRect.x = 20;
        scoreRect.y = 10;
    }
    SDL_FreeSurface(textSurface);
}


void HUD::update(int score, int bestScore, SDL_Renderer* renderer) {
    // Display current Score
    if (score != currentScore) {
        currentScore = score;
        loadText(renderer, currentScore, false);
    }

    // Display BestScore
    int currBest = std::max(score, bestScore);
    if (currBest != currentBestScore) {
        currentBestScore = currBest;
        loadText(renderer, currBest, true);
    }

    // Fallback
    if (scoreTexture == NULL) loadText(renderer, currentScore < 0 ? 0 : currentScore, false);
    if (bestScoreTexture == NULL) loadText(renderer, currentBestScore < 0 ? 0 : currentBestScore, true);
}


void HUD::render(SDL_Renderer* renderer) {
    if (scoreTexture) SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    if (bestScoreTexture) SDL_RenderCopy(renderer, bestScoreTexture, NULL, &bestScoreRect);
}