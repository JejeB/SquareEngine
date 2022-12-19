#pragma once
#include "utils/Vector.hpp"
#include <map>

class SDL_Renderer;

namespace Sq {
	class GraphicObject {
	protected:
		Vector _origin;
		const GraphicObject * _parent;
		unsigned int _id;
	public:
		GraphicObject(float x, float y, const GraphicObject* parent) :_origin(Vector{x,y}),_parent(parent),_id(0){}
		virtual void init(SDL_Renderer* renderer) {};
		virtual void update() {};
		virtual void render(SDL_Renderer* renderer) {};
		virtual void events( std::map<int, bool>& _keys) {};

		void set_origin(Vector v) { _origin = v; }
		Vector get_origin()const { return _origin; }
	};
}
