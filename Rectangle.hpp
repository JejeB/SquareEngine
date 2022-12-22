#pragma once
#include <string>
#include "GraphicObject.hpp"
#include "utils/Color.hpp"

struct SDL_Texture;
struct SDL_Rect;

namespace Sq {
	class Rectangle : public GraphicObject {
	protected:
		Vector _size; /*< Vector that represent the size of the rectangle x is the width and y the height*/
		Color _color; /*< Color of the border of the rectangle */
		std::string _sprite_path; /* < Path of the sprite to display*/
		SDL_Texture* _sprite;  /*< Data of the sprite texture*/
		bool _on_collision; /*< True if on collision*/

	public:
		/** Classic Constructor of a DynamicsRectangle
		*
		* @param x float, postion on the x axis
		* @param y float, positon on the y axis
		* @param with float, size on the x axis
		* @param height float, size on the y axis
		* @param GraphicObject * parent, parent of the object
		*/
		Rectangle(float x, float y, float w, float h, const GraphicObject* parent);
		
		/**
		* Init the sprite if there is one 
		*/
		void init(SDL_Renderer* renderer)override;
		void update()override {};
		/*
		* Draw the rectangle
		* @param renderer, drawing context of th window
		*/
		void render(SDL_Renderer* renderer)override;

		/**
		* Set the border color of the rectangle
		*/
		void setColor(const Color& c) { _color = c; }
		/**
		* Add a sprite for the rectangle. The sprite will be displayed ass the size of the rectangle.
		* @param string path, sprite to add all image format supported
		*/
		void add_sprite(const std::string& path) { _sprite_path = path; }

		/**
		* Return the size of the rectangle
		*/
		const Vector get_size() const { return _size; }
		
		/**
		*  Set the collision state
		*/
		void set_collision(bool c) { _on_collision = c; }
		
		/*
		* Reset the collisions to zero
		*/
		virtual void reset();

	private:
		void compute_outline(SDL_Rect* rect);
	};
}
