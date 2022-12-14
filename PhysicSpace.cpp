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
	//Update Dynmacis positions
	for  (auto dyn:_dynamics)
	{
		Vector instant_velo = dyn->get_velocity().by(_dT);
		//SDL_Log("%f %f %f", instant_velo.x, instant_velo.y,_dT);
		dyn->translate(instant_velo);
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
	auto dyn = dynamic_cast<DynamicRectangle*>(item);
	if (dyn) {
		_dynamics.push_back(dyn);
		auto stat = dynamic_cast<StaticRectangle*>(item);
		if (stat)
			_statics.push_back(stat);
	}
}

void Sq::PhysicSpace::removeItem(GraphicObject* item)
{
	//TODO
}
