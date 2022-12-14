#include "Rectangle.hpp"
#include "SDL.h"
#include "SDL_image.h"

Sq::Rectangle::Rectangle(float x, float y, float w, float h, const GraphicObject* parent) :GraphicObject(x, y, parent), _size(Vector{ w,h }), _color(Color{ -1,-1,-1 }), _sprite(NULL), _on_collision(false)
{}

void Sq::Rectangle::init(SDL_Renderer* renderer) {
	if (!_sprite_path.empty()) {
		SDL_Surface* image = IMG_Load(_sprite_path.c_str());
		_sprite = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
	}
}

void Sq::Rectangle::compute_outline(SDL_Rect* rect) {
	if (_parent != NULL) {
		rect->x = (int)(_parent->get_origin().x + _origin.x);
		rect->y = (int)(_parent->get_origin().y + _origin.y);
	}
	else {
		rect->x = (int)_origin.x;
		rect->y = (int)_origin.y;
	}
	rect->w = _size.x;
	rect->h = _size.y;
}

void Sq::Rectangle::render(SDL_Renderer* renderer) {
	SDL_Rect rect;
	compute_outline(&rect);
	if (_color.r != -1) {
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, 100);
		SDL_RenderDrawRect(renderer, &rect);
	}
	if (_sprite != NULL) {
		SDL_RenderCopy(renderer, _sprite, nullptr, &rect);
	}
	reset();
}

void Sq::Rectangle::reset() {
	_on_collision = false;
}