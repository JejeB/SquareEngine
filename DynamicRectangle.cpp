#include "DynamicRectangle.hpp"

#include "SDL.h"

Sq::DynamicRectangle::DynamicRectangle(float x, float y, float width, float height, const GraphicObject* parent) :Sq::Rectangle(x, y, width, height, parent), _velocity(Vector{0,0}) 
{}