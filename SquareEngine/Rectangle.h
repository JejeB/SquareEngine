#pragma once
#include"utils/Vector.h"
#include "utils/Color.h"
#include <SDL.h>
#include <string>
#include<map>
#include <SDL_image.h>

class Scene;

class Rectangle
{
	Vector _pos;
	int _width;
	int _height;
	SDL_Rect _rect_dis;
	Color _color;
	Vector _instant_velocity;
	Vector _velocity;
	Vector _contact_point;
	Scene* _scene;
	bool _in_collision;

	bool _is_affected_by_gravity;
	const float GRAV = 9.8;
	const float MAX_DROP = 500;

	std::string _sprite_path;
	SDL_Texture * _sprite;

public:
	Rectangle(float x, float y, int w, int h, Color c);
	Rectangle(Vector pos, int w, int h);


	const Vector& get_pos(){return _pos;}
	void set_pos(Vector p) { _pos = p; }
	void set_pos_x(float x) { _pos.x = x; }
	void set_pos_y(float y) { _pos.y = y; }

	Vector get_velocity() { return _velocity; }
	void set_velocity(Vector velocity);
	
	void set_scene(Scene* s) { _scene = s; }

	Vector get_contact_point() { return _contact_point; }
	
	void add_sprite(const std::string path) { _sprite_path = path; }
	
	void init(SDL_Renderer* renderer);
	void update(float dT);
	void draw(SDL_Renderer * renderer);
	void translate(Vector v);
	bool ray_collision(Vector r_origin, Vector r_dest, int width, int heigth,Vector & normal);
	void add_gravity() { _is_affected_by_gravity = true; }

	void event(SDL_Event _event);
	

private:
	void update_rect();
	void check_collision(float dT);
	void rigid_body_collision_resolve(float dT, std::map<float, Rectangle*> collisions);
	void on_collision(std::map<float, Rectangle*> collisions);
};