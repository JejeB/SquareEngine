#include "DynamicRectangle.hpp"

Sq::DynamicRectangle::DynamicRectangle(float x, float y, float width, float height, const GraphicObject* parent) :Sq::Rectangle(x, y, width, height, parent), _velocity(Vector{ 0,0 }), _other_velo({0,0})
{}

void Sq::DynamicRectangle::reset()
{
	Sq::Rectangle::update();
	_other_velo = Vector{ 0,0 };
}

void Sq::DynamicRectangle::update()
{
	
	_velocity = _velocity + _other_velo;
}

void Sq::DynamicRectangle::add_velocity(const Vector& v)
{ 
	_other_velo = _other_velo + v;
}
