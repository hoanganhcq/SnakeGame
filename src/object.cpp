#include "object.h"

Object::Object() {
    src = {0, 0, 0, 0};
    dest = {0, 0, 0, 0};
    texture = NULL;
    angle = 0;
    flip = SDL_FLIP_NONE;
}


SDL_Rect& Object::getSrc() {
    return src;
}


SDL_Rect& Object::getDest() {
    return dest;
}


void Object::setSrc(int x, int y, int w, int h) {
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}


void Object::setDest(int x, int y, int w, int h) {
	dest.x = x;
	dest.y = y;
	dest.h = h;
	dest.w = w;
}


void Object::setTexture(std::string id) {
    texture = TextureManager::Instance()->getTexture(id);

    // Automatically set the src size using the image size
    if (texture != NULL) {
        SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
    }
}


void Object::update() {

}


void Object::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopyEx(renderer, texture, &src, &dest, angle, NULL, flip);
    }
}