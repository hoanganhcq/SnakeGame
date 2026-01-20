#include "inputBox.h"

InputBox::InputBox(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h) {
    rect = {x, y, w, h};
    borderColor = {255, 255, 255, 255}; //white
    textColor = {255, 255, 255, 255};

    text = "";
    texture = NULL;

    backgroundColor = {0, 0, 0, 100};
    placeholder = "Enter Name";
    placeholderColor = {150, 150, 150, 255}; // Light Gray

    isFocused = false;
    maxLength = 10;

    updateTexture(renderer, font);
}


InputBox::~InputBox() {
    if (texture) SDL_DestroyTexture(texture);
}


void InputBox::updateTexture(SDL_Renderer* renderer, TTF_Font* font) {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }


    std::string displayString = text;
    SDL_Color displayColor = textColor;

    if (text.empty()) {
        displayString = placeholder;
        displayColor = placeholderColor;
    }

    if (placeholder.empty()) return;


    SDL_Surface* surface = TTF_RenderText_Solid(font, displayString.c_str(), displayColor);
    if (surface == NULL) return;
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    textRect.w = surface->w;
    textRect.h = surface->h;

    textRect.x = rect.x + 10;
    textRect.y = rect.y + (rect.h - textRect.h) / 2;

    SDL_FreeSurface(surface);
}


void InputBox::handleEvent(SDL_Event* e, SDL_Renderer* renderer, TTF_Font* font) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int mx = e->button.x;
        int my = e->button.y;

        bool insideBox = (mx >= rect.x && mx <= rect.x + rect.w &&
                         my >= rect.y && my <= rect.y + rect.h);

        isFocused = insideBox;

        if (isFocused) {
            SDL_StartTextInput();
            borderColor = {0, 255, 0, 255};
        } else {
            SDL_StopTextInput();
            borderColor = {255, 255, 255, 255};
        }
    }

    if (isFocused) {
        bool textChanged = false;

        if (e->type == SDL_TEXTINPUT) {
            if ((int)text.length() < maxLength) {
                text += e->text.text;
                textChanged = true;
            }
        }else if (e->type == SDL_KEYDOWN) {
            if (e->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
                text.pop_back();
                textChanged = true;
            }
            // Copy/Paste...
        }

        if (textChanged) {
            updateTexture(renderer, font);
        }
    }
}


void InputBox::render(SDL_Renderer* renderer) {
    // Background
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Border
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Draw Text
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
    }
}


std::string InputBox::getText() const {
    return text;
}