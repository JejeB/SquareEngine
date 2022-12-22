#pragma once
#include "GraphicObject.hpp"
#include <vector>
#include <map>
class SDL_Renderer;

namespace Sq {
	class DynamicRectangle;
	class StaticRectangle;
	class Rectangle;
	/**
	* Graphics object that containt rectangles, is will move the dynamics rectangle and compute the collisions and the resolutions.
	* You can also have another PhysicSpace inside, for example one for the HUD and another for the game. 
	*/
	class PhysicSpace : public GraphicObject{
		std::vector<GraphicObject*> _items; /*< All the items that will be displayed by the space*/
		std::vector<DynamicRectangle*> _dynamics; /*< Link on the dynamcis rectangles present in the space */
		std::vector<StaticRectangle*> _statics; /*< Link on the statics rectangles present in the space*/
		bool _debug; /*< Use to know if it's in debug mode*/
		float _dT; /*< Time elapsed between last frame*/
	public:
		/**
		* @param x float, postion on the x axis
		* @param y float, positon on the y axis
		* @param GraphicObject * parent, parent of the object
		*/
		PhysicSpace(float x, float y, const GraphicObject* parent);
		
		/**
		* Init all items
		*/
		void init(SDL_Renderer* renderer)override;
		
		/**
		*  Update all object and compute the physic for the dynamics rectangle
		*/
		void update()override;
		
		/**
		* Render all items
		*/
		void render(SDL_Renderer * renderer)override;
		
		/**
		* Propagate all the events to the items
		*/
		void events(std::map<int, bool>& _keys)override;

		/**
		* Add an item to the space
		* @param GraphicObject * item, pointer of the object to add
		*/
		void addItem(GraphicObject * item);
		
		/**
		* Set the debug mode, it will show the origin of the space
		*/
		void set_debug() { _debug = true; }
		
		/**
		* Set the time between to frame
		*/
		void set_delta_time(float dT) { _dT = dT; }

	private:
		void set_dynamics_vs_statics(DynamicRectangle* dyn);
		bool ray_collision(Vector dist, const DynamicRectangle* dyn, const StaticRectangle* st, Vector& normal, Vector& contact_point, float& t_hit_near);
		void resolve_rigid_body_collisions(DynamicRectangle* dyn, const std::multimap<float, StaticRectangle*>& collisions);

		void collisions_detection(DynamicRectangle* dyn);
		bool rectangle_vs_rectangle_collision(const Rectangle* r1, const Rectangle* r2);
	};
}