#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "SquareEngine.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Vector.h"

int main(int argc, char* argv[])
{
    int width = 1080;
    int height = 720;
    srand(time(NULL));
    SquareEngine sq(width, height);

    Scene s;
    s.set_debug();
    s.set_origin(Vector{0,0 });
    sq.set_Scene(&s);

    Rectangle r(100,100,200,20,Color{0,0,255});
    r.set_velocity(Vector{ 200,0 });
    s.add_item(&r);
    
    Rectangle r2(400, 0, 20, 20, Color{ 0,0,255 });
    r2.set_velocity(Vector{ 0,500 });
    s.add_item(&r2);

    sq.game_init();
    while (sq.is_game_up())
    {
        if (r.get_pos().x < 0 || r.get_pos().x>800) {
            r.set_velocity(r.get_velocity().opp());
        }
        if (r2.get_pos().y < 0 || r2.get_pos().y>200) {
            r2.set_velocity(r2.get_velocity().opp());
        }

        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}