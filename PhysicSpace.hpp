#pragma once
#include "GraphicObject.hpp"
#include <vector>

class SDL_Renderer;

namespace Sq {
	class PhysicSpace : public GraphicObject{
		std::vector<GraphicObject*> _items;
		bool _debug;
	public:
		PhysicSpace(float x, float y, const GraphicObject* parent);
		void init(SDL_Renderer* renderer)override;
		void update()override;
		void render(SDL_Renderer * renderer)override;

		void addItem(GraphicObject * item);
		void removeItem(GraphicObject* item);

		void set_debug() { _debug = true; }

	};
}