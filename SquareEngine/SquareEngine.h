#pragma once
#include<SDL.h>
#include "Scene.h"

class Rectangle;

class SquareEngine
{
	int _width;
	int _height;
	SDL_Window* _pWindow;
	SDL_Renderer* _pRenderer;
	SDL_Event _events;
	bool _isOpen;
	Scene * _scene;
	Uint32 _last_update;
	Vector _mouse_pos;
	Vector r_test_col;
	Rectangle* _rect;

public:
	SquareEngine(int w, int h);
	void set_Scene(Scene* s) { _scene = s; }
	
	bool is_game_up() { return _isOpen; }
	Vector mouse_pos() { return _mouse_pos; }
	
	int game_init();
	void game_loop();
	void game_close();
};

