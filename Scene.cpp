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
	_dt = dT;
	for (Rectangle* item : _items) {
		item->update();
	}
	compute_rects_velocities();
	detect_collisions();
	resolve_collisions();
	updates_positons();
}

void Scene::compute_rects_velocities() {
	for (Rectangle* item : _items) {
		item->compute_velocity();
	}
}

void Scene::detect_collisions() {
	for (Rectangle* item : _items) {
		item->check_collision();
	}
}

void Scene::resolve_collisions() {
	for (Rectangle* item : _items) {
		item->resolve_collision();
	}
}

void Scene::updates_positons() {
	for (Rectangle* item : _items) {
		item->update_positon();
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