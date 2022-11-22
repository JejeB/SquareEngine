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
    srand(time(NULL));
    SquareEngine sq(1080, 720);

    Scene s;
    s.set_debug();
    s.set_origin(Vector{30,100 });
    sq.set_Scene(&s);

    std::vector<Rectangle *> army;
    for (int i = 0; i < 70; i++) {
        Rectangle * soldier= new Rectangle(rand()%300, rand() % 300, 5, 5, Color{255,255,255});
        army.push_back(soldier);
        s.add_item(soldier);
    }

    Rectangle r3(300, 400, 300, 20, Color{ 255,0,255 });
    s.add_item(&r3);
    Rectangle r1(500, 30, 30, 500, Color{ 255,255,255 });
    s.add_item(&r1);

    

    sq.game_init();
    while (sq.is_game_up())
    {
        for (auto soldier : army) {
            soldier->set_velocity((s.map_to_view(sq.mouse_pos()) - soldier->get_pos()).by(5));
        }
        sq.game_loop();
    }
    sq.game_close();
    return EXIT_SUCCESS;
}