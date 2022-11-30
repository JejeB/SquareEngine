#include "SquareEngine.h"
#include "SDL.h"
#include <cstdlib>
#include <time.h>

using namespace Sq;

SquareEngine::SquareEngine(int w, int h): _width(w),_height(h),_pWindow(nullptr),_pRenderer(nullptr),_events(),_isOpen(true),_scene(nullptr),_last_update(),_mouse_pos() 
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

        _scene->init(_pRenderer);
    srand((unsigned int)time(NULL));
    _last_update = SDL_GetTicks();
    return EXIT_SUCCESS;
}

void SquareEngine::game_loop() {
    int x; int y;
        while (SDL_PollEvent(&_events))
        {
            switch (_events.type)
            {
            case SDL_QUIT:
                _isOpen = false;
                break;
            }

            
        }
        SDL_PumpEvents();
        SDL_GetMouseState(&x, &y);
        _mouse_pos.x = (float)x;
        _mouse_pos.y = (float)y;
        SDL_SetRenderDrawColor(_pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(_pRenderer);

        Uint32 time = SDL_GetTicks();
        float dT = (time - _last_update) / 1000.0f;
        if (_scene != NULL) {
            //Update
            _scene->update(dT);
            _last_update = time;
            //Draw
            _scene->draw(_pRenderer);
        }

        SDL_RenderPresent(_pRenderer);
}

void SquareEngine::game_close() {
    SDL_Log("close");
    SDL_DestroyRenderer(_pRenderer); 
    SDL_DestroyWindow(_pWindow);
    SDL_Quit();
}