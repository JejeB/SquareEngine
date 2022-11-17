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
	void init();
	
	void add_item(Rectangle * r);
	void set_debug() { _debug = true; };
	void set_origin(Vector c) { _origin = c; }
	Vector get_origin() { return _origin; }
	void update(float dT);
	void draw(SDL_Renderer* renderer);

private:
	void draw_debug(SDL_Renderer* renderer);
};

