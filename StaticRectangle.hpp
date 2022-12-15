#pragma once
#include "Rectangle.hpp"

namespace Sq {
	class StaticRectangle :public Rectangle {
	public:
		StaticRectangle(float x, float y, float w, float h, const GraphicObject* parent);
	};
}