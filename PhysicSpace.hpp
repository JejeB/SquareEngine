#include "GraphicObject.hpp"
#include <vector>

class SDL_Renderer;

namespace Sq {
	class PhysicSpace :  GraphicObject{
		std::vector<GraphicObject*> _items;
	public:
		PhysicSpace(float x, float y, GraphicObject* parent);
		void init()override;
		void update()override;
		void render(SDL_Renderer * renderer)override;

		void addItem(GraphicObject * item);
		void removeItem(GraphicObject* item);

		void set_origin(Vector origin);

	};
}