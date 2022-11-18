#include <cstdlib>
#include <SDL.h>

#include "SquareEngine.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Vector.h"

int main(int argc, char* argv[])
{
    SquareEngine sq(1080, 720);

    Scene s;
    s.set_debug();
    s.set_origin(Vector{30,100 });
    sq.set_Scene(&s);

    
    Rectangle r2(520, 500, 20, 20, Color{ 255,255,255 });
    s.add_item(&r2);

    Rectangle r1(500, 30, 3, 500, Color{ 255,255,255 });
    s.add_item(&r1);

    Rectangle r3(520, 30, 9, 500, Color{ 255,255,255 });
    s.add_item(&r3);

    

    sq.game_init();
    while (sq.is_game_up())
    {
        Vector r = r2.get_pos();
        r2.set_velocity( (s.map_to_view(sq.mouse_pos())-r).by(5));
        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}