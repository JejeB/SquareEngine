#pragma once
#include "Rectangle.hpp"
#include "utils/Vector.hpp"
namespace Sq {
	class GraphicObject;

	class DynamicRectangle : public Rectangle {
		Vector _velocity;
		Vector _forces;

	public:
		DynamicRectangle(float x, float y, float width, float height, const GraphicObject * parent);

		void reset()override;

		void add_forces(const Vector& v);

		void set_velocity(const Vector& v) { _velocity = v; }
		Vector get_velocity() { return _velocity + _forces; }

		void set_width(float w) { _size.x = w; };
		void set_height(float h) { _size.y = h; };

		void translate(const Vector& v) { _origin = _origin + v; }
	};
}