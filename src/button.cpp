#include "button.h"

Button::Button(SDL_Renderer* renderer, TTF_Font* font, std::string text, int x, int y) {
    // Color settings
    textNormalColor = {255, 255, 255, 255}; // white
    textHoverColor = {255, 255, 0, 255};    // yellow

    bgNormalColor = {50, 50, 50, 255};      // dark gray
    bgHoverColor = {100, 100, 100, 255};    // lighter gray

    isHovered = false;

    // Create the text surface first to get the dimensions
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textNormalColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect.x = x;
    rect.y = y;
    rect.w = surface->w + (paddingX * 2);
    rect.h = surface->h + (paddingY * 2); 

    // Center the text within the button frame
    textRect.w = surface->w;
    textRect.h = surface->h;
    textRect.x = rect.x + paddingX;
    textRect.y = rect.y + paddingY;

    SDL_FreeSurface(surface);
}


Button::Button() {
}


Button::~Button() {
    if (texture) SDL_DestroyTexture(texture);
}


void Button::render(SDL_Renderer* renderer) {
    // Draw the Background first
    if (isHovered) {
        SDL_SetRenderDrawColor(renderer, bgHoverColor.r, bgHoverColor.g, bgHoverColor.b, bgHoverColor.a);
    } else {
        SDL_SetRenderDrawColor(renderer, bgNormalColor.r, bgNormalColor.g, bgNormalColor.b, bgNormalColor.a);
    }
    SDL_RenderFillRect(renderer, &rect);

    // Bordering
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderDrawRect(renderer, &rect);

    // Draw Text
    if (isHovered) {
        SDL_SetTextureColorMod(texture, textHoverColor.r, textHoverColor.g, textHoverColor.b);
    } else {
        SDL_SetTextureColorMod(texture, textNormalColor.r, textNormalColor.g, textNormalColor.b);
    }
    
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}


bool Button::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool inside = true;
        if (mouseX < rect.x || mouseX > rect.x + rect.w ||
            mouseY < rect.y || mouseY > rect.y + rect.h) {
            inside = false;
        }

        isHovered = inside;

        if (inside && e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
            return true;
        }
    }
    return false;
}


void Button::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;

    textRect.x = rect.x + paddingX;
    textRect.y = rect.y + paddingY;
}