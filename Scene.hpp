#pragma once
#include "SDL.h"
#include <vector>

#include "Rectangle.hpp"
#include "utils/Vector.hpp"

namespace Sq {
	class SquareEngine;

	/*\brief Scene to display rectangle
	*
	* The scene is a infine space to store and display the rectangle, by default the origin is at the same that the window bt you can change it
	*
	*/
	class Scene
	{
		SquareEngine* _engine;
		Vector _origin;/* Origin of the scene it will be the 0,0 point foir all the rectangles*/
		std::vector<Rectangle*> _items; /* List of rectangle to display and manage*/
		bool _debug; /*Boolean to know if the class is in debug mode*/
	public:
		Scene(SquareEngine* engine);
		void init(SDL_Renderer* renderer);
		/* \brief return all the items from the scene as readonly
		*  \return : list of all rectangle in the scene
		*/
		std::vector<Rectangle*> get_items() const { return _items; }
		/* \brief add a new rectangle to the scene
		*
		*/
		void add_item(Rectangle* r);
		/*\brief call this fonction to activate the debug mode
		*
		*/
		void set_debug() { _debug = true; };

		/*\brief set a new origin to the scene
		*\param : Vector of the new origin in the window coordinates
		*/
		void set_origin(const Vector c) { _origin = c; }
		Vector get_origin() const { return _origin; }

		std::map<int, bool> get_keys() const;

		Vector map_to_scene(Vector v) { return v - _origin; }
		Vector map_to_view(Vector v) { return  _origin - v; }

		void set_Camera(Vector focus, int width, int height) { _origin.x = width / 2 - focus.x; _origin.y = height / 2 - focus.y; }

		void update(float dT);
		void draw(SDL_Renderer* renderer);

	private:
		void draw_debug(SDL_Renderer* renderer);
	};
}

