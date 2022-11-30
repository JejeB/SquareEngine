#pragma once
#include"utils/Vector.h"
#include "utils/Color.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include<map>

class Scene;
/*! \class Rectangle
 * \brief classe of a playable rectangle 
 * 
 *
 *  A rectangle is the main class of the engine. The main function is to display a 2D rectangle, you can add behiavors that can be usefull for a game.
 *	The posibilities are : add a velocity, collision detection, rigidbody colliosions resolution, sprite display and gravity. Your are free to use them all or combine them as you like. 
 * 
 */

class Rectangle
{
	Vector _pos; /*!<  Top left corner of the rectangle*/
	int _width; /* !< Size on the horizontal axis*/
	int _height; /* !< Size on the vertical axis*/

	Color _color; /* !< Color to display the border of the rect*/
	SDL_Rect _rect_dis; /* !< SDL_Rect used to display the rect. He's mapped on the scene coord*/
	
	Vector _instant_velocity; /* !< Velocity used after colliosion correction*/
	Vector _velocity; /*!< Initial velocity asked by the client*/
	Vector _contact_point; /*!< Last collions dectection contact point used for debug */

	const Scene * _scene; /*!< Pointer to the scene where the rectangle is in*/

	bool _is_affected_by_gravity; /* !< If true the object is affected to gravity*/
	const float GRAV = (float)9.8; /* !< Gravity constant */
	const float MAX_DROP = (float)500; /* !< Max y speed gravity*/

	std::string _sprite_path; /* !< Path of the sprite to display*/
	SDL_Texture * _sprite;  /*!< Data of the sprite texture*/

public:
	Rectangle(const Scene* scene, float x, float y, int w, int h, Color c, std::string sprite_path);
	Rectangle(const Scene* scene, float x, float y, int w, int h, std::string sprite_path);
	Rectangle(const Scene* scene, float x, float y, int w, int h, Color c);
	Rectangle(const Scene* scene, float x, float y, int w, int h);

	/*!
	* \brief Get the top corner of the rectangle
	* 
	*/
	const Vector get_pos(){return _pos;}
	
	/*!
	*\brief Set the rectangle to a new position
	* 
	*/
	void set_pos(Vector p) { _pos = p; }
	
	/*!
	*\brief Set the rectangle to a new x position
	*
	*/
	void set_pos_x(float x) { _pos.x = x; }
	
	/*!
	*\brief Set the rectangle to a new y position
	*
	*/
	void set_pos_y(float y) { _pos.y = y; }
	
	/*!
	*\brief Get the wanted velocity of the rectangle
	*
	*/
	const Vector get_velocity() { return _velocity; }

	/*!
	*\brief Set the wanted velocity
	*
	*/
	void set_velocity(Vector velocity);

	Vector get_contact_point() { return _contact_point; }
	
	void add_sprite(const std::string path) { _sprite_path = path; }
	
	/*!
	*\brief Call before the game loop
	*
	* \param renderer : the SDL_Renderer used to init the sprites if the are somes
	*/
	void init(SDL_Renderer* renderer);

	/*!
	*\brief Call inside the game loop
	*  This method do all the computation that are needed for the the rectangle, like new posiiton after speed collioisions ect...
	*  \param dT: delta since the last call of the funciton
	*/
	void update(float dT);
	/*!
	*\brief Call at the end of the game loop
	* 
	* Generate the renderer of the rectangle 
	*\param renderer: SDL_Renderer to be updated
	*/
	void draw(SDL_Renderer * renderer);

	/*!
	*\brief Detect collions from another moving rectangle
	*
	* This function detec if a vector is in collision with the rectangle
	* \param r_origin : origin of the vector that will be check
	* \param r_origin : origin of the vector that will be check
	* \param r_origin : origin of the vector that will be check
	*/
	bool ray_collision(const Vector r_origin,const Vector r_dest, int width, int heigth,Vector & normal);
	
	/*!
	*\brief Affect gravity to the rectangle
	*/
	void add_gravity() { _is_affected_by_gravity = true; }

	void event(SDL_Event _event);
	

private:
	void update_rect();
	void check_collision(float dT);
	void rigid_body_collision_resolve(float dT, const std::map<float, Rectangle*> collisions);
	void on_collision(std::map<float, Rectangle*> collisions);
};