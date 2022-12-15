#pragma once
#include <string>
#include "GraphicObject.hpp"
#include "utils/Color.hpp"

struct SDL_Texture;
struct SDL_Rect;

namespace Sq {
	class Rectangle : public GraphicObject {
	protected:
		Vector _size;
		Color _color;
		std::string _sprite_path; /* !< Path of the sprite to display*/
		SDL_Texture* _sprite;  /*!< Data of the sprite texture*/
		bool _on_collision;

	public:
		Rectangle(float x, float y, float w, float h, const GraphicObject* parent);
		void init(SDL_Renderer* renderer)override;
		void update()override {};
		void render(SDL_Renderer* renderer)override;

		void setColor(const Color& c) { _color = c; }

		void add_sprite(const std::string& path) { _sprite_path = path; }

		const Vector get_size() const { return _size; }

		void set_collision(bool c) { _on_collision = c; }

		void reset();

	private:
		void compute_outline(SDL_Rect* rect);
	};
}
