#include <algorithm>
#include <functional>
#include <math.h>
#include <map>

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
	_is_affected_by_gravity = false;
	_sprite_path.clear();
}

void Rectangle::init(SDL_Renderer* renderer){
	/*if (!_sprite_path.empty()) {
		SDL_Surface* image = IMG_Load(_sprite_path.c_str());
		 _sprite = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	}*/
}

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
	if (_is_affected_by_gravity) {
		_velocity.y = GRAV + _velocity.y;
		_velocity.y = _velocity.y > MAX_DROP ? MAX_DROP : _velocity.y;
	}
	_instant_velocity = _velocity;

	check_collision(dT);
	_pos = _pos+ _instant_velocity.by(dT);
}

void Rectangle::check_collision(float dT) {
	std::map<float, Rectangle*> collisions;
	
	for (auto r : _scene->get_items()) {
		Vector n;
		if (r != this) {
			if (r->ray_collision(_pos, _pos + _instant_velocity.by(dT),_width,_height,n)) {
				const float dist = _pos.dist(r->get_contact_point());
				collisions[dist] = r;
			}
		}
	}
	if (collisions.size() == 0) {
		_in_collision = false;
	}
	else {
		_in_collision = true;
		on_collision(collisions);
		rigid_body_collision_resolve(dT, collisions);
	}
}

void Rectangle::rigid_body_collision_resolve(float dT, std::map<float, Rectangle*> collisions) {
	//Resolve collision test again to check if is still in collision with another rectangle
	for (auto it : collisions) {
		Vector normal;
		if (it.second->ray_collision(_pos, _pos + _instant_velocity.by(dT), _width, _height, normal)) {
			Vector correction = _instant_velocity.abs() * normal;
			_instant_velocity = _instant_velocity + correction;
		}
	}
}

void Rectangle::on_collision(std::map<float, Rectangle*> collisions){

}

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

void Rectangle::draw(SDL_Renderer* renderer) {
	update_rect();
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, 255);
	SDL_RenderDrawRect(renderer,&_rect_dis);

	/*if (_sprite != NULL) {
		SDL_RenderCopy(renderer, _sprite, nullptr, &_rect_dis);
	}*/
}

void Rectangle::translate(Vector v) {
	_pos = _pos +v;
}