#pragma once
#include <SDL.h>
#include <vector>

#include "Vector.h"

#include "Rectangle.h"

class Scene
{
	Vector _origin;
	std::vector<Rectangle*> _items;
	bool _debug;
public:
	Scene();
	void init(SDL_Renderer* renderer);
	
	std::vector<Rectangle*> get_items() { return _items; }
	void add_item(Rectangle * r);

	void set_debug() { _debug = true; };
	void set_origin(Vector c) { _origin = c; }
	Vector get_origin() { return _origin; }
	

	Vector map_to_scene(Vector v) { return v - _origin; }
	Vector map_to_view(Vector v) { return  _origin-v; }
	
	void set_Camera(Vector focus, int width, int height) { _origin.x = width / 2 - focus.x; _origin.y = height / 2 - focus.y; }
	
	void update(float dT);
	void draw(SDL_Renderer* renderer);

	void event(SDL_Event _event);

private:
	void draw_debug(SDL_Renderer* renderer);
};

