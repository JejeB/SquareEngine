#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"

#include "SquareEngine.hpp"
#include "Scene.hpp"
#include "Rectangle.hpp"
#include "utils/Vector.hpp"

int main(int argc, char* argv[])
{
    int width = 1080;
    int height = 720;
    srand((unsigned int)time(NULL));
    Sq::SquareEngine sq(width, height);

    Sq::Scene s;
    s.set_debug();
    s.set_origin(Vector{100,100 });
    sq.set_Scene(&s);

    Sq::Rectangle player(&s,500,0,30,30,Color{255,0,255});
    s.add_item(&player);

    Sq::Rectangle ob1(&s,400, 400, 200, 40, Color{ 255,255,255 });
    s.add_item(&ob1);

    Sq::Rectangle ob2(&s, 50, 100, 50, 100, Color{ 255,255,255 });
    s.add_item(&ob2);

    Sq::Rectangle ob3(&s, 500, 100, 50, 100, Color{ 255,255,255 });
    s.add_item(&ob3);

    Sq::Rectangle ob4(&s, 400, 200, 50, 50, Color{ 255,255,255 });
    s.add_item(&ob4);

    sq.game_init();
    while (sq.is_game_up())
    {
        Vector v = s.map_to_scene(sq.mouse_pos())- player.get_pos();
        player.set_velocity(v.by(10));
        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}