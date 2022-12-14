#include "PhysicSpace.hpp"

#include "SDL.h"

Sq::PhysicSpace::PhysicSpace(float x, float y, const GraphicObject* parent):GraphicObject(x,y,parent),_debug(false)
{}

void Sq::PhysicSpace::init(SDL_Renderer* renderer)
{
	for (auto item : _items) {
		item->init(renderer);
	}
}

void Sq::PhysicSpace::update()
{

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
}

void Sq::PhysicSpace::removeItem(GraphicObject* item)
{
	//TODO
}
