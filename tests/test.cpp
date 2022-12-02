#include "../Scene.hpp"
#include "../Rectangle.hpp"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_session.hpp>

int main(int argc, char* args[])
{
    int result = Catch::Session().run(argc, args);

    // global clean-up...

    return result;
}

TEST_CASE("Init scene") {
    Sq::Scene scene;
    REQUIRE(scene.get_items().size() == 0);
}
