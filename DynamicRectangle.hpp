#pragma once
#include "StaticRectangle.hpp"
#include "utils/Vector.hpp"
namespace Sq {
	class GraphicObject;

	class DynamicRectangle : public StaticRectangle {
		Vector _velocity;

	public:
		DynamicRectangle(float x, float y, float width, float height, const GraphicObject * parent);

		void set_velocity(const Vector& v) { _velocity = v; }
		Vector get_velocity() { return _velocity; }

		void set_width(float w) { _size.x = w; };
		void set_height(float h) { _size.y = h; };

		void translate(const Vector& v) { _origin = _origin + v; }
	};
}
 