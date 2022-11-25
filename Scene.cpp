#include "Scene.h"

#include "SDL.h"

#include "Rectangle.h"

Scene::Scene():_debug(false){
	_origin.x = 0; _origin.y = 0;
}

void Scene::init(SDL_Renderer* renderer) {
	for (Rectangle* item : _items) {
		item->init(renderer);
	}
}


void Scene::add_item(Rectangle * r) {
	r->set_scene(this);
	_items.push_back(r);
}

void Scene::update(float dT) {
	for (Rectangle *item : _items) {
		item->update(dT);
	}
}

void Scene::event(SDL_Event _event) {
	for (Rectangle* item : _items) {

	}
}

void Scene::draw(SDL_Renderer * renderer) {
	if (_debug) {
		draw_debug(renderer);
	}
	for (Rectangle* item : _items) {
		item->draw(renderer);
	}
}

void Scene::draw_debug(SDL_Renderer* renderer) {
	// X axis
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLineF(renderer, _origin.x, _origin.y, _origin.x+100,_origin.y);

	//Y axis
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLineF(renderer, _origin.x, _origin.y, _origin.x, _origin.y +100);
}