#pragma once
#include <string>
#include "GraphicObject.hpp"
#include "utils/Color.hpp"

struct SDL_Texture;
struct SDL_Rect;

namespace Sq {
	class StaticRectangle : public GraphicObject{
	protected:
		Vector _size;
		Color _color;
		std::string _sprite_path; /* !< Path of the sprite to display*/
		SDL_Texture* _sprite;  /*!< Data of the sprite texture*/
	public:
		StaticRectangle(float x, float y,float w,float h,const GraphicObject* parent);
		 void init(SDL_Renderer* renderer)override;
		 void update()override {};
		 void render(SDL_Renderer* renderer)override;

		 void setColor(const Color& c) { _color = c; }

		 void add_sprite(const std::string& path) { _sprite_path = path; }
	private:
		void compute_outline(SDL_Rect* rect);
	};
}
