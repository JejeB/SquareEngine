#include "StaticRectangle.hpp"
#include "SDL.h"
#include "SDL_image.h"

Sq::StaticRectangle::StaticRectangle(float x, float y,float w,float h, const GraphicObject* parent):GraphicObject(x,y,parent),_bottom_right(Vector{x+w,y+h}),_color(Color{-1,-1,-1}),_sprite(NULL)
{}

void Sq::StaticRectangle::init(SDL_Renderer* renderer) {
	if (!_sprite_path.empty()) {
		SDL_Surface* image = IMG_Load(_sprite_path.c_str());
		_sprite = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
	}
}

void Sq::StaticRectangle::render(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = _origin.x; rect.y = _origin.y; rect.w = width(); rect.h = height();
	if (_color.r != -1) {
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, 100);
		SDL_RenderDrawRect(renderer, &rect);
	}
	if (_sprite != NULL) {
		SDL_RenderCopy(renderer, _sprite, nullptr, &rect);
	}
}
