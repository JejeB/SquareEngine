#pragma once
#include "utils/Vector.hpp"
#include <map>

class SDL_Renderer;

namespace Sq {
	/**
	* @brief Class that represent a an object that can be displayed, the class do nothing by himself. 
	*/
	class GraphicObject {
	protected:
		Vector _origin; /*< position in a 2D space of the object*/
		const GraphicObject * _parent; /*< Parent object, the origin of the 2D space of the object is the postion of the parent*/
	public:
		/**
		* @param x float, postion on the x axis
		* @param y float, positon on the y axis
		* @param GraphicObject * parent, parent of the object
		*/
		GraphicObject(float x, float y, const GraphicObject* parent) :_origin(Vector{x,y}),_parent(parent){}
		
		/**
		* Init all the data before the game loop
		* @param SDL_Renderer * renderer, pointer on the renderer used to init the sprites
		*/
		virtual void init(SDL_Renderer* renderer) {};
		
		/** 
		* Call during the game loop, this will be call before the frame display and before the physic engine 
		*/
		virtual void update() {};
		
		/**
		* Call just before the frame, use this function if you need to modify a color or a sprite
		*/
		virtual void render(SDL_Renderer* renderer) {};
		
		/**
		* Call when a keyboard is pressed. 
		* @param map keys, map will contain all the state of the keyboard key that are down
		*/
		virtual void events( std::map<int, bool>& _keys) {};
		
		/**
		* Change the object to a new origin
		* @param Vector v, new origin
		*/
		void set_origin(Vector v) { _origin = v; }
		/**
		* Get the current origin of the object
		* @return Vector, origin of the object
		*/
		Vector get_origin()const { return _origin; }
	};
}
