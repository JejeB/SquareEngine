#include "DynamicRectangle.hpp"

Sq::DynamicRectangle::DynamicRectangle(float x, float y, float width, float height, const GraphicObject* parent) :Sq::Rectangle(x, y, width, height, parent), _velocity(Vector{ 0,0 }), _forces({0,0})
{}

void Sq::DynamicRectangle::reset()
{
	_on_collision = false;
	_forces = Vector{ 0,0 };
}

void Sq::DynamicRectangle::add_forces(const Vector& v)
{ 
	_forces = _forces + v;
}
