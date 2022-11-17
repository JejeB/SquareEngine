#pragma once
#include"Vector.h"
#include "Color.h"
#include <SDL.h>

class Scene;

class Rectangle
{
	Vector _pos;
	int _width;
	int _height;
	SDL_Rect _rect_dis;
	Color _color;
	Vector _velocity;
	Scene* _scene;

public:
	Rectangle(float x, float y, int w, int h, Color c);
	Rectangle(Vector pos, int w, int h);
	const Vector& get_pos(){return _pos;}
	void set_velocity(Vector velocity);
	void set_scene(Scene* s) { _scene =s; }
	void init();
	void update(float dT);
	void draw(SDL_Renderer * renderer);
	void translate(Vector v);
	bool is_in_collision(const Rectangle& r);

private:
	void update_rect();
	void check_collision();
};