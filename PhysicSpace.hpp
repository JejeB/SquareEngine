#pragma once
#include "GraphicObject.hpp"
#include <vector>

class SDL_Renderer;

namespace Sq {
	class DynamicRectangle;
	class StaticRectangle;

	class PhysicSpace : public GraphicObject{
		std::vector<GraphicObject*> _items;
		std::vector<DynamicRectangle*> _dynamics;
		std::vector<StaticRectangle*> _statics;
		bool _debug;
		float _dT;
	public:
		PhysicSpace(float x, float y, const GraphicObject* parent);
		void init(SDL_Renderer* renderer)override;
		void update()override;
		void render(SDL_Renderer * renderer)override;

		void addItem(GraphicObject * item);
		void removeItem(GraphicObject* item);

		void set_debug() { _debug = true; }

		void set_delta_time(float dT) { _dT = dT; }

	private:
		void set_dynamics_vs_statics(DynamicRectangle* dyn);
		bool ray_collision(Vector dist, const DynamicRectangle* dyn, const StaticRectangle* st, Vector& normal, Vector& contact_point, float& t_hit_near);
		};
}