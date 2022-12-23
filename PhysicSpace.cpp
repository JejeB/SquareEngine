#include "PhysicSpace.hpp"

#include "SDL.h"
#include "DynamicRectangle.hpp"
#include "StaticRectangle.hpp"
#include "Rectangle.hpp"

Sq::PhysicSpace::PhysicSpace(float x, float y, const GraphicObject* parent):GraphicObject(x,y,parent),_debug(false),_dT(0)
{}

void Sq::PhysicSpace::init(SDL_Renderer* renderer)
{
	for (auto item : _items) {
		item->init(renderer);
	}
}

void Sq::PhysicSpace::update()
{
	for (auto item : _items)
		item->update();
	//Dynamics vs statics coll
	for (auto dyn : _dynamics) 
		set_dynamics_vs_statics(dyn);
	//Update Dynmacis positions
	for  (auto dyn : _dynamics)
		dyn->translate(dyn->get_velocity().by(_dT));
	//Do all detection collisions
	for (auto dyn : _dynamics)
		collisions_detection(dyn);
}

void Sq::PhysicSpace::set_dynamics_vs_statics(DynamicRectangle* dyn) {
	std::multimap<float, StaticRectangle*> collisions;
	Vector instant = dyn->get_velocity().by(_dT);
	for (auto s : _statics) {
		Vector normal; Vector contact_point; 
		float time;
		if (ray_collision(instant, dyn, s, normal, contact_point, time)) {
			float collisions_distance = dyn->get_origin().dist(contact_point);
			collisions.insert({ collisions_distance,s });// The map is automaticly sort by collisions distance
		}
	}
	//if rigid_body resolve colliosion
	resolve_rigid_body_collisions(dyn, collisions);
}

void Sq::PhysicSpace::resolve_rigid_body_collisions(Sq::DynamicRectangle* dyn, const std::multimap<float, StaticRectangle*>& collisions) {
	for (const auto it : collisions) {
		Vector normal; Vector contact; float time;
		Vector instant = dyn->get_velocity().by(_dT);
		if (ray_collision(instant, dyn, it.second, normal, contact, time)) {
			Vector correction = ((dyn->get_velocity().abs() * normal).by(1 - time));
			if (time >= 0.0 && time < 1) {
				dyn->add_forces(correction);
				//set_dynamics_vs_statics(dyn); // We need to do a recurution to test if the corrected vector don't collide with a rectangle
			}
		}
	}
}

void Sq::PhysicSpace::collisions_detection(DynamicRectangle* dyn)
{
	for (Rectangle* r : _statics) {
		if (rectangle_vs_rectangle_collision(dyn,r) ) {
			r->set_collision(true);
			dyn->set_collision(true);
		}
	}
	for (Rectangle* r : _dynamics) {
		if (r!=dyn && rectangle_vs_rectangle_collision(dyn, r)) {
			r->set_collision(true);
			dyn->set_collision(true);
		}
	}
}

bool Sq::PhysicSpace::rectangle_vs_rectangle_collision(const Sq::Rectangle* r1, const Sq::Rectangle* r2)
{
	if (r1->get_origin().x + r1->get_size().x >= r2->get_origin().x &&
		r1->get_origin().y + r1->get_size().y >= r2->get_origin().y &&
		r1->get_origin().x <= r2->get_origin().x + r2->get_size().x &&
		r1->get_origin().y <= r2->get_origin().y + r2->get_size().y) {
		return true;
	}
	else {
		return false;
	}
}

void Sq::PhysicSpace::render(SDL_Renderer *renderer)
{
	for (auto item:_items)
	{
		item->render(renderer);
	}
	if (_debug) {
		// X axis
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawLineF(renderer, _origin.x, _origin.y, _origin.x + 100, _origin.y);

		//Y axis
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawLineF(renderer, _origin.x, _origin.y, _origin.x, _origin.y + 100);
	}
}

void Sq::PhysicSpace::events(std::map<int, bool>& _keys)
{
	for (auto item : _items) {
		item->events(_keys);
	}
}

void Sq::PhysicSpace::addItem(GraphicObject* item)
{
	_items.push_back(item);

	if (dynamic_cast<DynamicRectangle*>(item))
		_dynamics.push_back(dynamic_cast<DynamicRectangle*>(item));
	
	if (dynamic_cast<StaticRectangle*>(item))
		_statics.push_back(dynamic_cast<StaticRectangle*>(item));
	
}


bool Sq::PhysicSpace::ray_collision(Vector dist,const DynamicRectangle *dyn, const StaticRectangle * st, Vector& normal, Vector& contact_point, float& t_hit_near) {

	
	Vector expand_pos = st->get_origin() - dyn->get_size();
	Vector expand_size = st->get_size() + dyn->get_size();
	Vector t_near = (expand_pos - dyn->get_origin()) / dist;
	Vector t_far = (expand_pos + expand_size - dyn->get_origin()) / dist;

	if (isnan(t_far.y) || isnan(t_far.x)) return false;
	if (isnan(t_near.y) || isnan(t_near.x)) return false;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	t_hit_near = std::max(t_near.x, t_near.y);

	// Furthest 'time' is contact on opposite side of target
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0 || t_hit_near>1) return false;

	
	contact_point.x = dyn->get_origin().x + t_hit_near * dist.x;
	contact_point.y = dyn->get_origin().y + t_hit_near * dist.y;

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
