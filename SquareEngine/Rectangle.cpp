#include <algorithm>
#include <functional>
#include <math.h>

#include "Rectangle.h"
#include "Scene.h"


Rectangle::Rectangle(Vector pos, int w, int h) :_pos(pos), _width(w), _height(h) {
	
	_scene = NULL;
}

Rectangle::Rectangle(float x, float y, int w, int h, Color c):_width(w),_height(h),_color(c) {
	_pos.x = x; _pos.y = y;
	_velocity.x = 0; _velocity.y=0;
	_contact_point.x = 0; _contact_point.y = 0;
	_in_collision = false;
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
	_desti = _pos + _velocity.by(dT);
	check_collision();
	_pos = _pos+ _velocity.by(dT);
	
	
}

void Rectangle::check_collision() {
	std::vector<Rectangle*> collider;
	std::vector<Vector> normals;
	for (auto r : _scene->get_items()) {
		Vector n;
		if (r != this) {
			if (r->ray_collision(_pos,_desti,_width,_height,n)) {
				collider.push_back(r);
				normals.push_back(n);
			}
		}
	}
	
	if (collider.size() == 0) {
		_in_collision = false;
		//_color = Color{ 255,255,255 };
	}
	else {
		_in_collision = true;
		for (auto v : normals) {
			Vector correction = _velocity.abs() * v;
			_velocity = _velocity + correction;
		}
	}
}

void Rectangle::collision(){}

bool Rectangle::ray_collision(Vector r_origin,Vector r_vec, int width_target, int height_target,Vector &normal) {
	
	Vector exp_pos{ _pos.x - width_target ,_pos.y - height_target };
	Vector exp_size; exp_size.x = _width + width_target; exp_size.y = _height + height_target;
	Vector dist = r_vec- r_origin;
	
	Vector t_near = (exp_pos - r_origin) / dist;
	Vector t_far = (exp_pos + exp_size - r_origin) / dist;

	

	if (isnan(t_far.y) || isnan(t_far.x)) return false;
	if (isnan(t_near.y) || isnan(t_near.x)) return false;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	float t_hit_near = std::max(t_near.x, t_near.y);

	// Furthest 'time' is contact on opposite side of target
	float t_hit_far = std::min(t_far.x, t_far.y);
	
	if (t_hit_far < 0 || t_hit_near>1) return false;

	_contact_point.x = r_origin.x + t_hit_near * dist.x;
	_contact_point.y = r_origin.y + t_hit_near * dist.y;

	if (t_near.x > t_near.y)
		if (dist.x < 0)
			normal = { 1, 0 };
		else
			normal = { -1, 0 };
	else if (t_near.x < t_near.y)
		if (dist.y < 0)
			normal = { 0, 1 };
		else
			normal = { 0, -1 };

	
	return true;

}

bool Rectangle::is_in_collision(const Rectangle& r) {
	if ((_pos.x >= r._pos.x + r._width) ||
		(_pos.x + _width <= r._pos.x) ||
		(_pos.y >= r._pos.y + r._height) ||
		(_pos.y + _height <= r._pos.y)) {
		return false;
	}
	else {
		return true;
	}
}

void Rectangle::draw(SDL_Renderer* renderer) {
	update_rect();
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, 255);
	SDL_RenderDrawRect(renderer,&_rect_dis);
	

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawLineF(renderer, _scene->get_origin().x+_pos.x, _scene->get_origin().y+_pos.y, _scene->get_origin().x+ _desti.x, _scene->get_origin().y+_desti.y);
	//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	//SDL_RenderDrawPoint(renderer, _scene->get_origin().x + _contact_point.x, _scene->get_origin().y + _contact_point.y);
}

void Rectangle::translate(Vector v) {
	_pos = _pos +v;
}