#include "Rectangle.h"
#include "Scene.h"


Rectangle::Rectangle(Vector pos, int w, int h) :_pos(pos), _width(w), _height(h) {
	
	_scene = NULL;
}

Rectangle::Rectangle(float x, float y, int w, int h, Color c):_width(w),_height(h),_color(c) {
	_pos.x = x; _pos.y = y;
	_velocity.x = 0; _velocity.y=0;
	_scene = NULL;
}

void Rectangle::init(){}

void Rectangle::set_velocity(Vector v) {
	_velocity = v;
}
void Rectangle::update_rect() {
	if (_scene != NULL) {
		_rect_dis.x = (int)_scene->get_origin().x + _pos.x;
		_rect_dis.y = (int)_scene->get_origin().y + _pos.y;
	}
	else {
		_rect_dis.x =  _pos.x;
		_rect_dis.y =  _pos.y;
	}
	_rect_dis.w = _width;
	_rect_dis.h = _height;
}

void Rectangle::update(float dT) {
	_pos = _pos+ _velocity.by(dT);
	SDL_Log("merde !");
	
}

void Rectangle::draw(SDL_Renderer* renderer) {
	update_rect();
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, 255);
	SDL_RenderDrawRect(renderer,&_rect_dis);
}

void Rectangle::translate(Vector v) {
	_pos = _pos +v;
}