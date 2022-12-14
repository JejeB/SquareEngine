# Square Engine

![logo](logo.png)

No rotation, no stranges shapes only rectangles !

This game project is a 2D game engine who work only with parallels squares. 
This engine focus on some pretty simples fonctions that you can combine to do lot of thing.
- Display a window
- A scene where you can add rectangles
- Display some rectangles 
- Add sprite to this rectangles
- Events detections
- Collisions detections and resolutions

Basicly this library is a wrap of the SDL2 with some useful functions that are boring to implement. 
It's a nice sandbox to do some prototyping or learning.

## Getting started
This small tutorial explain you how to launch a demo projet on Linux and windows. 
The library use `CMAKE`, `SDL2` and `SDL2 IMAGE` so you need to install this to dependencies.

### Install dependencies Linux

If you don't have it install CMAKE.

```
sudo apt-get install cmake
```

Install the SDL with apt don't work a lot, It's better with `aptitude`. So first install aptitude :

```
sudo apt-get aptitude
```

Then the SDL and SDL IMAGE

```
sudo aptitude install libsdl2-dev -y
sudo aptitude install libsdl2-image-dev -y
```

### Install dependencies Windows

- You can install the cmake gui from [here](https://cmake.org/download/).
- Download the `SDL2-devel-[]-VC.zip` [here](https://github.com/libsdl-org/SDL/releases).
- Download the `SDL2_image-devel-[]-VC.zip` [here](https://github.com/libsdl-org/SDL_image/releases).

Unzip `SDL2-devel-[]-VC.zip` and `SDL2_image-devel-[]-VC.zip` in a folder of your choice.

### Create a demo project :

Create a `Main.cpp` file :

``` c++
#include "SquareEngine.hpp"
#include "PhysicSpace.hpp"
#include "DynamicRectangle.hpp"
#include "StaticRectangle.hpp"
#include "utils/Vector.hpp"

int main(int argc, char* argv[])
{
    int width = 1080;
    int height = 720;
    Sq::SquareEngine sq(width, height); //Init the Engine

    Sq::PhysicSpace scene(0, 0, NULL);
    sq.set_root_space(&scene);

    Sq::DynamicRectangle p(10, 10, 30, 50, &scene);
    p.setColor(Color{ 250,0,250 });
    scene.addItem(&p);

    Sq::StaticRectangle obstacle1(100, 500, 800, 5, &scene);
    obstacle1.setColor(Color{ 250,250,250 });
    scene.addItem(&obstacle1);

    sq.game_init(); // At the end call the init method() it will load the sprites if there are somes
    while (sq.is_game_up()) // Loop since the game is up
    {
        p.set_velocity((sq.mouse_pos() - p.get_origin()).by(5)); // Make the purple rectangle follow the mouse
        sq.game_update();
        sq.game_frame_renderer();
    }
    sq.game_close(); // Free memory etc...
    return EXIT_SUCCESS;
}
```

Then clone the library in the same folder

```
git clone https://github.com/JejeB/SquareEngine
```

Then create the ``CMakeLists.txt` :

```cmake
cmake_minimum_required(VERSION 3.10)

project(Demo)

set (SRCS Main.cpp)
add_subdirectory(SquareEngine)
add_executable(Demo ${SRCS})
target_link_libraries(Demo PUBLIC SquareEngine)
target_include_directories(Demo PUBLIC SquareEngine)
```

### Compilation on Linux

Well its pretty easy

```
cmake .
make
./Demo
```

You should have a nice window and a square following your mouse !

### Compilation on Windows

You can use the cmake-gui to generate a Visual Studio Solution. Often it doesn't find the SDL IMAGE by itself so you need to do it by hand:
- Link SDL2_IMAGE_INCLUDE_DIR to `{Where you extract the libs}/SDL2_image-2.6.2/include`
- Link SDL2_IMAGE_INCLUDE_LIBRARY to `{Where you extract the libs}/SDL2_image-2.6.2/lib/x64/SDL2_image.lib`

The click `Configure` then `Generate`. After that if everything work you can `Open Project`. 

Sometime Visual Studio create useless project `ALL_BUILD` and `ZERO_CHECK`, you can just right click and unload them.

When you try to run the prject iyt will say that there are missing the `.dll`, you can find them in the `lib\x64\` folder of the `SDL2` and `SDL2_image library` 


 
