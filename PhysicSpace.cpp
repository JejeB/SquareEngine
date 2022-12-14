#include "PhysicSpace.hpp"

#include "SDL.h"
#include "DynamicRectangle.hpp"
#include "StaticRectangle.hpp"

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
	//Dynamics vs statics coll
	for (auto dyn : _dynamics) {
		set_dynamics_vs_statics(dyn);
	}

	//Update Dynmacis positions
	for  (auto dyn:_dynamics)
		dyn->translate(dyn->get_velocity().by(_dT));
}

void Sq::PhysicSpace::set_dynamics_vs_statics(DynamicRectangle* dyn) {
	for (auto s : _statics) {
		Vector instant= dyn->get_velocity().by(_dT);
		Vector normal; Vector contact_point; 
		float time;
		bool b = ray_collision(instant, dyn, s, normal, contact_point, time);
		SDL_Log("%d", b);
		if (b) {
			dyn->set_collision(true);
			s->set_collision(true);
		}
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

void Sq::PhysicSpace::addItem(GraphicObject* item)
{
	_items.push_back(item);

	if (dynamic_cast<DynamicRectangle*>(item))
		_dynamics.push_back(dynamic_cast<DynamicRectangle*>(item));
	
	if (dynamic_cast<StaticRectangle*>(item))
		_statics.push_back(dynamic_cast<StaticRectangle*>(item));
	
}

void Sq::PhysicSpace::removeItem(GraphicObject* item)
{
	//TODO
}

bool Sq::PhysicSpace::ray_collision(Vector r_vec,const Sq::DynamicRectangle* dyn_rect,const Sq::StaticRectangle* static_rect, Vector& normal, Vector& contact_point, float& t_hit_near) {

	Vector expand_origin = static_rect->get_origin() - dyn_rect->get_size();
	Vector expand_size = static_rect->get_size() + dyn_rect->get_size();
	Vector dist = r_vec - dyn_rect->get_origin();

	Vector t_near = (expand_origin - dyn_rect->get_origin()) / dist;
	Vector t_far = (expand_origin + expand_size - dyn_rect->get_origin()) / dist;

	if (isnan(t_far.y) || isnan(t_far.x)) return false;
	if (isnan(t_near.y) || isnan(t_near.x)) return false;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	t_hit_near = std::max(t_near.x, t_near.y);

	// Furthest 'time' is contact on opposite side of target
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0 || t_hit_near>1 || t_hit_near < 0) return false;

	contact_point.x = dyn_rect->get_origin().x + t_hit_near * dist.x;
	contact_point.y = dyn_rect->get_origin().y + t_hit_near * dist.y;

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