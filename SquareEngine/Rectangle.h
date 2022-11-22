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
	Vector _desti;
	Vector _contact_point;
	Scene* _scene;
	bool _in_collision;

public:
	Rectangle(float x, float y, int w, int h, Color c);
	Rectangle(Vector pos, int w, int h);
	const Vector& get_pos(){return _pos;}
	void set_velocity(Vector velocity);
	Vector get_velocity() { return _velocity; }
	void set_scene(Scene* s) { _scene =s; }
	void set_pos(Vector p) { _pos = p; }
	void set_pos_x(float x) { _pos.x = x; }
	void set_pos_y(float y) { _pos.y = y; }
	void init();
	void update(float dT);
	void draw(SDL_Renderer * renderer);
	void translate(Vector v);
	bool is_in_collision(const Rectangle& r);
	bool ray_collision(Vector r_origin, Vector r_dest, int width, int heigth,Vector & normal);
	void collision();

private:
	void update_rect();
	void check_collision();
};