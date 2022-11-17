#include <cstdlib>
#include <SDL.h>

#include "SquareEngine.h"
#include "Scene.h"
#include "Rectangle.h"

int main(int argc, char* argv[])
{
    SquareEngine sq(800, 600);
    
    Scene s;
    s.set_debug();
    s.set_origin(Vector{ 50,50 });
    sq.set_Scene(&s);

    
    Rectangle r1(50, 50, 50, 50, Color{ 255,255,255 });
    r1.set_velocity(Vector{ 100,0 });
    s.add_item(&r1);

    Rectangle r2(200, 50, 20, 20, Color{ 255,255,255 });
    r2.set_velocity(Vector{ 0,300 });
    s.add_item(&r2);


    sq.game_init();
    while (sq.is_game_up())
    {
        
        if (r2.get_pos().y > 100) {
            r2.set_velocity(Vector{ 0,-300 });
        }
        if (r2.get_pos().y <0)
        {
            r2.set_velocity(Vector{ 0,300 });
        }
        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}