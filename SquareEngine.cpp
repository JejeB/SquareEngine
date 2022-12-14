#include "SquareEngine.hpp"
#include "SDL.h"
#include <cstdlib>
#include <time.h>

#include "PhysicSpace.hpp"

using namespace Sq;

SquareEngine::SquareEngine(int w, int h): _width(w),_height(h),_pWindow(nullptr),_pRenderer(nullptr),_isOpen(true),_last_update(),_mouse_pos(),_delta(0),_root_space(NULL)
{}

int SquareEngine::game_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
        if (SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_SHOWN, &_pWindow, &_pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());        
        SDL_Quit(); 
        return EXIT_FAILURE;
    }

     
    srand((unsigned int)time(NULL));
    _last_update = SDL_GetTicks();

    if (_root_space != NULL) {
        _root_space->init(_pRenderer);
    }

    return EXIT_SUCCESS;
}

void SquareEngine::game_update() {
    Uint32 time = SDL_GetTicks();
    _delta = (time - _last_update);
    if (_delta > 1000 / fps_cap) {
        manage_events();
        //Draw background

        SDL_SetRenderDrawColor(_pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(_pRenderer);
        float dT = _delta / 1000.0f;

        //update rootPhysicSpace
        if (_root_space != NULL) {
            _root_space->update();
        }
        
        _last_update = time;
    }
}

void SquareEngine::game_frame_renderer() {
    if (_delta > 1000 / fps_cap) {
        if (_root_space != NULL) {
            _root_space->render(_pRenderer);
        }
        SDL_RenderPresent(_pRenderer);
    }
    
}

void SquareEngine::manage_events() {
    int x; int y;

    SDL_Event _events; /* List of the events that happend on the windows */
    while (SDL_PollEvent(&_events))
    {
        switch (_events.type)
        {
        case SDL_QUIT:
            _isOpen = false;
            break;
        case SDL_KEYDOWN:
            _keys[_events.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            _keys[_events.key.keysym.sym] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            //SDL_Log("Mouse Down");
            break;
        case SDL_MOUSEBUTTONUP:
            //SDL_Log("Mouse Up");
            break;
        }
    }
    
    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);
    _mouse_pos.x = (float)x;
    _mouse_pos.y = (float)y;
}
void SquareEngine::game_close() {
    SDL_DestroyRenderer(_pRenderer); 
    SDL_DestroyWindow(_pWindow);
    SDL_Quit();
}