#include "button.h"

// Create Button by Text
Button::Button(SDL_Renderer* renderer, TTF_Font* font, std::string text, int x, int y) {
    useImage = false;
    normalTexture = NULL;
    hoverTexture = NULL;
    // Color settings
    textNormalColor = {255, 255, 255, 255}; // white
    textHoverColor = {255, 255, 0, 255};    // yellow

    bgNormalColor = {50, 50, 50, 255};      // dark gray
    bgHoverColor = {100, 100, 100, 255};    // lighter gray

    isHovered = false;

    // Create the text surface first to get the dimensions
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textNormalColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, surface);

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


// Create Button by Image
Button::Button(SDL_Renderer* renderer, SDL_Texture* normal, SDL_Texture* hover, int x, int y, int w, int h) {
    useImage = true;
    normalTexture = normal;
    hoverTexture = hover;
    textTexture = NULL;
    isHovered = false;

    rect.x = x;
    rect.y = y;

    if (w > 0 && h > 0) {
        rect.w = w;
        rect.h = h;
    } else {
        int imgW, imgH;
        SDL_QueryTexture(normalTexture, NULL, NULL, &imgW, &imgH);
        rect.w = imgW;
        rect.h = imgH;
    }

}


Button::Button() {
}


Button::~Button() {
    if (textTexture) SDL_DestroyTexture(textTexture);
    if (normalTexture) SDL_DestroyTexture(normalTexture);
    if (hoverTexture) SDL_DestroyTexture(hoverTexture);
}


void Button::render(SDL_Renderer* renderer) {
    if (useImage) {
        SDL_Texture* currentTexture = isHovered ? hoverTexture : normalTexture;
        if (currentTexture) {
            SDL_RenderCopy(renderer, currentTexture, NULL, &rect);
        }
    } else {
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
        if (textTexture) {
            if (isHovered) {
                SDL_SetTextureColorMod(textTexture, textHoverColor.r, textHoverColor.g, textHoverColor.b);
            } else {
                SDL_SetTextureColorMod(textTexture, textNormalColor.r, textNormalColor.g, textNormalColor.b);
            }
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        }  
    }
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

    if (!useImage) {
        textRect.x = rect.x + paddingX;
        textRect.y = rect.y + paddingY;
    }
}