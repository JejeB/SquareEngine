#include <algorithm>
#include <functional>
#include <math.h>
#include <map>

#include "Rectangle.hpp"
#include "Scene.hpp"

using namespace Sq;

Rectangle::Rectangle(const Scene* scene, float x, float y, int w, int h, Color c,std::string sprite_path):_pos(Vector{x,y}), _width(w), _height(h), _color(c),_rect_dis(),_velocity(Vector{0,0}),
_wanted_velocity(Vector{ 0,0 }), _contact_point(Vector{0,0}), _scene(scene), _is_affected_by_gravity(false), _sprite_path(sprite_path),_sprite(nullptr)
{}

Rectangle::Rectangle(const Scene* scene, float x, float y, int w, int h) :_pos(Vector{ x,y }), _width(w), _height(h), _color(Color{0,0,0}), _rect_dis(), _velocity(Vector{ 0,0 }),
_wanted_velocity(Vector{ 0,0 }), _contact_point(Vector{ 0,0 }), _scene(scene), _is_affected_by_gravity(false), _sprite_path(""), _sprite(nullptr)
{}

Rectangle::Rectangle(const Scene* scene, float x, float y, int w, int h, std::string sprite_path) :_pos(Vector{ x,y }), _width(w), _height(h), _color(Color{ 0,0,0 }), _rect_dis(), _velocity(Vector{ 0,0 }),
_wanted_velocity(Vector{ 0,0 }), _contact_point(Vector{ 0,0 }), _scene(scene), _is_affected_by_gravity(false), _sprite_path(sprite_path), _sprite(nullptr)
{}

Rectangle::Rectangle(const Scene* scene, float x, float y, int w, int h, Color c) :_pos(Vector{ x,y }), _width(w), _height(h), _color(c), _rect_dis(), _velocity(Vector{ 0,0 }),
_wanted_velocity(Vector{ 0,0 }), _contact_point(Vector{ 0,0 }), _scene(scene), _is_affected_by_gravity(false), _sprite_path(""), _sprite(nullptr)
{}

void Rectangle::init(SDL_Renderer* renderer){
	if (!_sprite_path.empty()) {
		SDL_Surface* image = IMG_Load(_sprite_path.c_str());
		 _sprite = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	}
}

std::map<int, bool> Rectangle::get_keys()  {
	return _scene->get_keys(); 
}

void Rectangle::set_velocity(Vector v) {
	_wanted_velocity = v;
}


void Rectangle::update() {
}

void Rectangle::compute_velocity() {
	Vector gravity{ 0,0 };
	if (_is_affected_by_gravity && _wanted_velocity.y == 0)
		gravity = compute_gravity();
	_velocity = _wanted_velocity + gravity;
}

void Rectangle::resolve_collision() {
	Vector collisions{ 0,0 };
	if (_is_rigid) {
		collisions = rigid_body_collision_resolve(_collision_rects);
		SDL_Log("Correction %f %f", collisions.x, collisions.y);
	}
		
	_velocity = _velocity + collisions;
}

const Vector Rectangle::compute_gravity() {
	Vector r{ 0,0 };
	r.y = GRAV + _velocity.y;
	r.y = _velocity.y > MAX_DROP ? MAX_DROP : r.y;
	return r;
}

void Rectangle::check_collision() {
	
	for (const auto r : _scene->get_items()) {
		Vector n; Vector c; float f;
		if (r != this) {
			if (r->ray_collision(_pos, _pos + instant_velo(), _width, _height, n, c,f)) {
				const float dist = _pos.dist(r->get_contact_point());
				//SDL_Log("Collisions: %f %f %f", _pos.x,_pos.y, instant_velo().y);
				_collision_rects[dist] = r; //Add the distance the the colliosion map, so the map is sorted by distance of collionsion
				r->add_coll(dist, this);
			}
		}
	}
}

void Rectangle::set_collisions() {
	if (_collision_rects.size() != 0) {
		on_collision();
		_on_collisions = true;
	}
}

void Rectangle::update_positon() {
	_pos = _pos + instant_velo();
}
const Vector Rectangle::rigid_body_collision_resolve(const std::map<float, Rectangle*>& collisions) {
	Vector correction{ 0,0 };
	//Resolve collision test again to check if is still in collision with another rectangle
	for (const auto it : collisions) {
		Vector normal; Vector contact; float f;
		if (it.second->ray_collision(_pos, _pos + instant_velo(), _width, _height, normal, contact,f)) {
				correction = correction + (_velocity.abs() * normal).by(1-f);	
		}
	}
	if (correction.x != 0) {
		SDL_Log("What !");
	}
	return correction;
}

void Rectangle::on_collision(){

}

bool Rectangle::ray_collision(Vector r_origin,Vector r_vec, int width_target, int height_target,Vector &normal,Vector &contact_point,float& t_hit_near) {
	
	Vector exp_pos{ _pos.x - width_target ,_pos.y - height_target };
	Vector exp_size; 
	exp_size.x = (float)(_width + width_target); 
	exp_size.y = (float)(_height + height_target);
	Vector dist = r_vec- r_origin;
	
	Vector t_near = (exp_pos - r_origin) / dist;
	Vector t_far = (exp_pos + exp_size - r_origin) / dist;

	if (isnan(t_far.y) || isnan(t_far.x)) return false;
	if (isnan(t_near.y) || isnan(t_near.x)) return false;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	t_hit_near = std::max(t_near.x, t_near.y);

	// Furthest 'time' is contact on opposite side of target
	float t_hit_far = std::min(t_far.x, t_far.y);
	
	if (t_hit_far < 0 || t_hit_near>1 || t_hit_near<0) return false;

	contact_point.x = r_origin.x + t_hit_near * dist.x;
	contact_point.y = r_origin.y + t_hit_near * dist.y;

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

void Rectangle::render(){}

void Rectangle::draw(SDL_Renderer* renderer) {
	update_rect();
	render();
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, 100);
	SDL_RenderDrawRect(renderer,&_rect_dis);

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDrawPoint(renderer, _contact_point.x, _contact_point.y);

	if (_sprite != NULL) {
		SDL_RenderCopy(renderer, _sprite, nullptr, &_rect_dis);
	}
}

Vector Rectangle::instant_velo() {
	 return _velocity.by(_scene->get_dT());
}

void Rectangle::clear() {
	_collision_rects.clear();
	_on_collisions = false;
}