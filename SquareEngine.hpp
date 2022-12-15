#pragma once
#include <map>
#include "utils/Vector.hpp"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Events;

namespace Sq {
	class PhysicSpace;

	class SquareEngine
	{
		int _width; /*Horizontal size of the game in pixels */
		int _height; /*Vertical size of the game in pixels */
		SDL_Window* _pWindow;/*Pointer of the SDL Windows used to dislpay the renderer*/
		SDL_Renderer* _pRenderer; /*Renderer that will be updated by the rectangles */
		bool _isOpen; /* Check if the game is still up*/
		int _last_update; /* Used to compute the time between two frame*/
		float _delta;
		Vector _mouse_pos; /* Mouse postions in the window coordinate*/
		std::map<int, bool> _keys;

		const float fps_cap = 60.0;

		PhysicSpace* _root_space;

	public:
		/* \brief Main class of the Engine
		* Start an instance of the Engine that will open a new window
		*
		* \param w : width of the window in pixels
		* \param w : height of the window in pixels
		*/
		SquareEngine(int w, int h);
		
		/*\brief Return if the game is still playing or not
		*
		* \return Boolean true if the game is still playing else false
		*/
		bool is_game_up() { return _isOpen; }
		/* \brief Get the mouse positon
		*
		* \return Vector of the mouse position in the window coordinate
		*/
		Vector mouse_pos() { return _mouse_pos; }
		/* \brief Get the key pressed at the moment
		* 
		* \return Map where the key is the key pressed and true if the key is down else false
		*/
		std::map<int, bool> get_keys() const { return _keys; }

		/*\brief call before the while loop
		*
		* \return the error code if fail
		*/
		int game_init();

		/* \brief call at the end of the while loop
		*
		* This function wile compute all the object interaction and draw them, you need to call it at the end of the while loop
		*/
		void game_update();

		void game_frame_renderer();
		/* \brief call after the while loop
		*
		*This function will close the game and free all the memory
		*/
		void game_close();

		void set_root_space(PhysicSpace* ps) { _root_space = ps; }

	private:
		void manage_events();
	};
}