#include "utils/Vector.hpp"

class SDL_Renderer;

namespace Sq {
	class GraphicObject {
	protected:
		Vector _origin;
		GraphicObject * _parent;
	public:
		GraphicObject(float x, float y, GraphicObject* parent) :_origin(Vector{x,y}),_parent(parent){}
		virtual void init() {};
		virtual void update() {};
		virtual void render(SDL_Renderer* renderer) {};

		void set_origin(Vector v) { _origin = v; }
		Vector get_origin()const { return _origin; }
	};
}
