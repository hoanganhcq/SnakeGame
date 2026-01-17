#include "menu.h"

Menu::Menu(SDL_Renderer* renderer, int screenWidth, int screenHeight, TTF_Font* globalFont) {

    font = globalFont;
    titleFont = globalFont;


    // Title "SNAKE GAME"
    SDL_Color titleColor = {0, 255, 0, 255}; // green
    SDL_Surface* surface = TTF_RenderText_Solid(titleFont, "SNAKE GAME", titleColor);
    titleTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    titleRect.w = surface->w;
    titleRect.h = surface->h;
    titleRect.x = (screenWidth - titleRect.w) / 2; 
    titleRect.y = screenHeight / 4;                
    
    SDL_FreeSurface(surface);


    // Create Buttons
    startButton = new Button(renderer, font, "START GAME", 0, 0);
    exitButton = new Button(renderer, font, "EXIT GAME", 0, 0);


    int centerX = screenWidth / 2;
    int startY = screenHeight / 2; 
    int gap = 20;

    // Center the Start button
    startButton->setPosition(
        centerX - (startButton->getWidth() / 2), 
        startY
    );

    // Center the Exit button
    exitButton->setPosition(
        centerX - (exitButton->getWidth() / 2), 
        startY + startButton->getHeight() + gap
    );
}

Menu::~Menu() {
    delete startButton;
    delete exitButton;
    
    if (titleTexture) SDL_DestroyTexture(titleTexture);
    if (font) TTF_CloseFont(font);
    if (titleFont) TTF_CloseFont(titleFont);
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

    startButton->render(renderer);
    exitButton->render(renderer);
}

int Menu::handleEvent(SDL_Event* e) {
    // press Start
    if (startButton->handleEvent(e)) {
        return 1;
    }
    
    // Press Exit
    if (exitButton->handleEvent(e)) {
        return 2;
    }

    return 0; // Do nothing
}