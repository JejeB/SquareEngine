#include <catch2/catch_test_macros.hpp>
#include "SDL.h"
#include "../Scene.hpp"
#include "../Rectangle.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Add a rect in scene") {
    Sq::Scene s;
    s.set_debug();
    s.set_origin(Vector{ 100,100 });

    Sq::Rectangle player(&s, 500, 0, 30, 30, Color{ 255,0,255 });
    s.add_item(&player);
    int verif = 1;
    REQUIRE( verif == 1);
}