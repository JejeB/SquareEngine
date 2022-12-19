#pragma once
#include "Rectangle.hpp"
#include "utils/Vector.hpp"
namespace Sq {
	class GraphicObject;

	class DynamicRectangle : public Rectangle {
		Vector _velocity;
		Vector _other_velo;

	public:
		DynamicRectangle(float x, float y, float width, float height, const GraphicObject * parent);

		void set_velocity(const Vector& v) { _velocity = v; }
		void add_velocity(const Vector& v) { _other_velo = _other_velo + v; }
		Vector get_velocity() { return _velocity; }

		void set_width(float w) { _size.x = w; };
		void set_height(float h) { _size.y = h; };

		void translate(const Vector& v) { _origin = _origin + v; }
	};
}
 