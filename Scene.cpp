#include "SquareEngine.hpp"
#include "Scene.hpp"
#include "Rectangle.hpp"

using namespace Sq;

Scene::Scene(SquareEngine* engine):_engine(engine), _origin(Vector{0,0}), _items(), _debug(false)
{}

void Sq::Scene::init(SDL_Renderer* renderer) {
	for (Rectangle* item : _items) {
		item->init(renderer);
	}
}


void Scene::add_item(Rectangle* r) {
	_items.push_back(r);
}

void Scene::update(float dT) {
	for (Rectangle* item : _items) {
		item->update(dT);
	}
	compute_rects_velocities(dT);
	detect_collisions(dT);
	resolve_collisions(dT);
	updates_positons(dT);
}

void Scene::compute_rects_velocities(float dT) {
	for (Rectangle* item : _items) {
		item->compute_velocity(dT);
	}
}

void Scene::detect_collisions(float dT) {
	for (Rectangle* item : _items) {
		item->check_collision(dT);
	}
}

void Scene::resolve_collisions(float dT) {
	for (Rectangle* item : _items) {
		item->resolve_collision(dT);
	}
}

void Scene::updates_positons(float dT) {
	for (Rectangle* item : _items) {
		item->update_positon(dT);
	}
}

std::map<int, bool> Scene::get_keys() const{
	return _engine->get_keys();
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