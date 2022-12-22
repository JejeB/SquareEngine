#pragma once
#include "Rectangle.hpp"
#include "utils/Vector.hpp"

namespace Sq {
	class GraphicObject;
	/* @brief A Rectangle that will move with a velocity, and his size can be changed.
	*
	*
	* The DynamicRectangle classes is a Graphics object that can be modified. You can modify his origin and size with directly with setters
	* but this is not the best way. To benefit for the collisions engine you need to add a velocity to the Rectangle to make it move. For 
	* that it's possible to change the velocity directly but it will erase all the other opération that you did before. If you have a complexe 
	* object with gravity and movement it's better to use add_force function.
	* 
	* To be displayed a Dynamic rectangle have to be in a PhysicsSpace that will do all the computing for collision and resolution.
	*/
	class DynamicRectangle : public Rectangle {
		
		Vector _velocity; /*< Velocity of the rectangle, the postion will be updated at each frame by time*/
		Vector _forces; /* < The forces that will be added at an instant the Rectangle*/

	public:
		/** Classic Constructor of a DynamicsRectangle
		*
		* @param x float, postion on the x axis
		* @param y float, positon on the y axis
		* @param with float, size on the x axis
		* @param height float, size on the y axis
		* @param GraphicObject * parent, parent of the object, to use the physic engine he have to be a PhysicSpace 
		*/
		DynamicRectangle(float x, float y, float width, float height, const GraphicObject * parent);

		/**
		* This method have to be call at the end of the frame display. It will reset all the instant variables to zero.
		*/
		void reset()override;
		
		/**
		* Add a force to the speed for a frame. If the function is call multiple time in the same frame the forces will be added.
		* @param Vector v, value of the force to be added.
		*/
		void add_forces(const Vector& v);
		
		/**
		* Set the velocity of the object. It will also erase all the beyond computing that had be done but the collisions will work fine.
		* @param Vector v, new velocity of the object
		*/
		void set_velocity(const Vector& v) { _velocity = v; }
		/**
		*  Return the velocity of an object. If force have been there will be included.
		* @return Vector, velocity of the object
		*/
		Vector get_velocity() { return _velocity + _forces; }

		/**
		* Set a new width to the object
		* @param float w, new width of the rectangle
		*/
		void set_width(float w) { _size.x = w; };

		/**
		* Set a new height to the object
		* @param float h, new height of the rectangle
		*/
		void set_height(float h) { _size.y = h; };
		/**
		* Teleport the rectangle to a newpositon with a certain vector. This position is use by the engine to move with the speed the object. 
		* @param Vector v, the translate vector to move the rectangle
		*/
		void translate(const Vector& v) { _origin = _origin + v; }
	};
}