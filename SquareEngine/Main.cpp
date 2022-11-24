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

    Rectangle player(500,0,20,40,Color{255,0,0});
    player.add_gravity();
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
        float v_x = s.map_to_scene(sq.mouse_pos()).x- player.get_pos().x;
        player.set_velocity( Vector{v_x,player.get_velocity().y});
        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}