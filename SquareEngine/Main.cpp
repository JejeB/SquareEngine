#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "SquareEngine.h"
#include "Scene.h"
#include "Rectangle.h"
#include "utils/Vector.h"

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

    Rectangle player(500,0,30,30,Color{0,0,255});
    player.add_sprite("sprite.gif");
    s.add_item(&player);

    Rectangle ob1(400, 400, 200, 40, Color{ 255,255,255 });
    s.add_item(&ob1);

    Rectangle ob2(50, 100, 50, 100, Color{ 255,255,255 });
    s.add_item(&ob2);

    Rectangle ob3(500, 100, 50, 100, Color{ 255,255,255 });
    s.add_item(&ob3);

    Rectangle ob4(400, 200, 50, 50, Color{ 255,255,255 });
    s.add_item(&ob4);

    sq.game_init();
    while (sq.is_game_up())
    {
        Vector v = s.map_to_scene(sq.mouse_pos())- player.get_pos();
        player.set_velocity(v.by(5));
        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}